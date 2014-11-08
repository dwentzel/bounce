#include <cstdio>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "logging/log.h"

#include "render_system.h"
#include "game_entity.h"

void bounce::RenderSystem::startup()
{
    renderer_.Startup();
}

void bounce::RenderSystem::shutdown() {
    renderer_.Shutdown();
}

namespace {
    
    glm::vec3 position = glm::vec3(0, 0, 15);
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;
}


void bounce::RenderSystem::update() {
    renderer_.SetupNewFrame();
    
    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));
    
    glm::vec3 position(0, 0, 5);
    float fov = initialFoV;
    
    glm::mat4 projection_matrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view_matrix = glm::lookAt(position, glm::vec3(0, 0, 0),
                                        glm::vec3(0, 1, 0));
    
//    glm::vec3 lightPos = glm::vec3(0,3,2);

    renderer_.SetViewMatrix(&view_matrix[0][0]);
    
    const GameEntityList& entities = world_manager_.entities();
    
    for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
        GameEntity* entity = *i;
        
        glm::mat4 model_matrix = glm::toMat4(entity->orientation());
        glm::mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;
        
        renderer_.SetMVPMatrix(&mvp_matrix[0][0]);
        renderer_.SetModelMatrix(&model_matrix[0][0]);
        
        entity->UpdateComponentOfType(RENDER_COMPONENT);
    }
    
    application_context_.Flush();
}

void bounce::RenderSystem::RenderModel(unsigned int model_handle)
{
    renderer_.RenderModel(model_handle);
    
//    const Model& model = model_manager_.GetModel(model_handle);
//    
//    const std::vector<int>& start_indices = model.mesh_start_indices();
//    const std::vector<int>& sizes = model.mesh_sizes();
//    const std::vector<int>& material_indices = model.material_indices();
//    
//    for (std::vector<int>::size_type i = 0; i != start_indices.size(); ++i) {
//        int start_index = start_indices[i];
//        int size = sizes[i];
//        int material_index = material_indices[i];
//        
//        const Material& material = material_manager_.GetMaterial(material_index);
//        
//        GLuint diffuse_index = glGetUniformLocation(program_id_, "Material_diffuse");
//        GLuint ambient_index = glGetUniformLocation(program_id_, "Material_ambient");
//        GLuint specular_index = glGetUniformLocation(program_id_, "Material_specular");
//        GLuint emissive_index = glGetUniformLocation(program_id_, "Material_emissive");
//        GLuint shininess_index = glGetUniformLocation(program_id_, "Material_shininess");
//        
//        glUniform3fv(diffuse_index, 1, material.diffuse());
//        glUniform3fv(ambient_index, 1, material.ambient());
//        glUniform3fv(specular_index, 1, material.specular());
//        glUniform3fv(emissive_index, 1, material.emissive());
//        glUniform1f(shininess_index, material.shininess());
//        
//        glDrawArrays(GL_TRIANGLES, start_index, size);
//        CHECK_GL_ERROR();
//    }
    
}
