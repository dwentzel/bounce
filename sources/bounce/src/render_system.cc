#include <cstdio>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "render_system.h"
#include "game_entity.h"
#include "bounce_gl.h"
#include "shader_manager.h"

void bounce::RenderSystem::startup() {
    CheckGlError();
    
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        //return -1;
        throw "Failed to initialze GLEW";
    }
    CheckGlError();
    
    glEnable(GL_DEPTH_TEST);
    CheckGlError();
    
    glDepthFunc(GL_LESS);
    CheckGlError();
    
    glClearDepth(1.0);
    CheckGlError();
    
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    CheckGlError();

    glGenBuffers(3, buffers_);
    
    CheckGlError();
    
    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stdout, "framebuffer not complete\n");
    }
    CheckGlError();
    
    ShaderManager shader_manager;
    
    program_id_ = shader_manager.loadShaders(
                                             "shaders/triangleShader.vert.glsl",
                                             "shaders/triangleShader.frag.glsl");
    
    matrix_id_ = glGetUniformLocation(program_id_, "mvp");
}

void bounce::RenderSystem::shutdown() {
    glDeleteBuffers(3, buffers_);
}

namespace {
    
    glm::vec3 position = glm::vec3(0, 0, 15);
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;
}


void bounce::RenderSystem::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CheckGlError();
    
    glUseProgram(program_id_);
    CheckGlError();
    
    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));
    
    glm::vec3 position(0, 0, 5);
    float fov = initialFoV;
    
    glm::mat4 projection = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view = glm::lookAt(position, glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    
    const GameEntityList& entities = world_manager_.entities();
    
    for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
        GameEntity* entity = *i;
        
        glm::mat4 model = glm::toMat4(entity->orientation());
        
        glm::mat4 mvp = projection * view * model;
        
        glUniformMatrix4fv(matrix_id_, 1, GL_FALSE, &mvp[0][0]);
        CheckGlError();
        
        entity->UpdateComponentOfType(RENDER_COMPONENT);
    }
    
    application_context_.flush();
    
}

void bounce::RenderSystem::BindArrayBuffer(int index) {
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[index]);
    CheckGlError();
}

void bounce::RenderSystem::BufferArrayData(int count, GLfloat* data) {
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    CheckGlError();
}

void bounce::RenderSystem::VertexAttribPointer(int index, int size) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
    CheckGlError();
}

void bounce::RenderSystem::EnableVertexAttribArray(int index) {
    glEnableVertexAttribArray(index);
    CheckGlError();
}

void bounce::RenderSystem::DisableVertexAttrib(int index) {
    glDisableVertexAttribArray(index);
    CheckGlError();
}