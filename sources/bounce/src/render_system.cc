#include <cstdio>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "logging/log.h"

#include "render_system.h"
#include "game_entity.h"
#include "bounce_gl.h"
#include "shader_manager.h"


namespace bounce {
    std::wostream& operator<<(std::wostream& out, const GLubyte* data)
    {
        if (data == nullptr) {
            out << L"(null)";
        }
        else {
            out << std::string(reinterpret_cast<const char*>(data));
        }
        return out;
    }
}

void bounce::RenderSystem::startup() {
    CHECK_GL_ERROR();
    
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        LOG_ERROR << L"Failed to initialize GLEW" << std::endl;
        //return -1;
        throw "Failed to initialze GLEW";
    }
    CHECK_GL_ERROR();
    
    const GLubyte* m = glGetString(GL_VENDOR);
    LOG_INFO << L"GL_VENDOR: " << m << std::endl;
    
    m = glGetString(GL_RENDERER);
    LOG_INFO << L"GL_RENDERER: " << m << std::endl;
    
    m = glGetString(GL_VERSION);
    LOG_INFO << L"GL_VERSION: " << m << std::endl;
    
    m = glGetString(GL_EXTENSIONS);
    LOG_INFO << L"GL_EXTENSIONS: " << m << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    CHECK_GL_ERROR();
    
    glDepthFunc(GL_LESS);
    CHECK_GL_ERROR();
    
    glClearDepth(1.0);
    CHECK_GL_ERROR();
    
    glEnable(GL_CULL_FACE);
    CHECK_GL_ERROR();
    
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    CHECK_GL_ERROR();
    
    //glGenBuffers(3, buffers_);
    glGenBuffers(1, buffers_);
    
    CHECK_GL_ERROR();
    
    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stdout, "framebuffer not complete\n");
    }
    CHECK_GL_ERROR();
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.current_size(), vertex_buffer_.buffer(), GL_STATIC_DRAW);
    
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    
    ShaderManager shader_manager;
    
    program_id_ = shader_manager.LoadShaders(
                                             "shaders/triangleShader.vert.glsl",
                                             "shaders/triangleShader.frag.glsl");
    
    mvp_matrix_id_ = glGetUniformLocation(program_id_, "MVP");
    view_matrix_id_ = glGetUniformLocation(program_id_, "V");
    model_matrix_id_ = glGetUniformLocation(program_id_, "M");
    
    light_id_ = glGetUniformLocation(program_id_, "LightPosition_worldspace");
    
    
}

void bounce::RenderSystem::shutdown() {
    glDeleteBuffers(1, buffers_);
}

namespace {
    
    glm::vec3 position = glm::vec3(0, 0, 15);
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;
}


void bounce::RenderSystem::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECK_GL_ERROR();
    
    glUseProgram(program_id_);
    CHECK_GL_ERROR();
    
    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));
    
    glm::vec3 position(0, 0, 5);
    float fov = initialFoV;
    
    glm::mat4 projection_matrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view_matrix = glm::lookAt(position, glm::vec3(0, 0, 0),
                                        glm::vec3(0, 1, 0));
    
    glUniformMatrix4fv(view_matrix_id_, 1, GL_FALSE, &view_matrix[0][0]);
    
    glm::vec3 lightPos = glm::vec3(0,3,2);
    glUniform3f(light_id_, lightPos.x, lightPos.y, lightPos.z);
    
    const GameEntityList& entities = world_manager_.entities();
    
    for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
        GameEntity* entity = *i;
        
        glm::mat4 model = glm::toMat4(entity->orientation());
        glm::mat4 mvp = projection_matrix * view_matrix * model;
        
        glUniformMatrix4fv(mvp_matrix_id_, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(model_matrix_id_, 1, GL_FALSE, &model[0][0]);
        CHECK_GL_ERROR();
        
        entity->UpdateComponentOfType(RENDER_COMPONENT);
    }
    
    application_context_.flush();
}

void bounce::RenderSystem::RenderModel(unsigned int model_handle)
{
    const Model& model = model_manager_.GetModel(model_handle);
    
    const std::vector<int>& start_indices = model.mesh_start_indices();
    const std::vector<int>& sizes = model.mesh_sizes();
    const std::vector<int>& material_indices = model.material_indices();
    
    for (std::vector<int>::size_type i = 0; i != start_indices.size(); ++i) {
        int start_index = start_indices[i];
        int size = sizes[i];
        int material_index = material_indices[i];
        
        const Material& material = material_manager_.GetMaterial(material_index);
        
        GLuint diffuse_index = glGetUniformLocation(program_id_, "Material_diffuse");
        GLuint ambient_index = glGetUniformLocation(program_id_, "Material_ambient");
        GLuint specular_index = glGetUniformLocation(program_id_, "Material_specular");
        GLuint emissive_index = glGetUniformLocation(program_id_, "Material_emissive");
        GLuint shininess_index = glGetUniformLocation(program_id_, "Material_shininess");
        
        glUniform3fv(diffuse_index, 1, material.diffuse());
        glUniform3fv(ambient_index, 1, material.ambient());
        glUniform3fv(specular_index, 1, material.specular());
        glUniform3fv(emissive_index, 1, material.emissive());
        glUniform1f(shininess_index, material.shininess());
        
        glDrawArrays(GL_TRIANGLES, start_index, size);
        CHECK_GL_ERROR();
    }
    
}
