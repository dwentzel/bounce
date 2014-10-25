#include <cstdio>
#include "render_system.h"
#include "bounce_gl.h"
#include "shader_manager.h"

void bounce::RenderSystem::startup() {
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        //return -1;
        throw "Failed to initialze GLEW";
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    ShaderManager shader_manager;
    
    program_id_ = shader_manager.loadShaders(
                                          "shaders/triangleShader.vert.glsl",
                                          "shaders/triangleShader.frag.glsl");
    
    matrix_id_ = glGetUniformLocation(program_id_, "mvp");
}

void bounce::RenderSystem::shutdown() {
    
}

void bounce::RenderSystem::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program_id_);
    
    const std::vector<GameEntity*>& entities = world_manager_.entities();
    
    for (std::vector<GameEntity*>::size_type i = 0; i < entities.size(); ++i) {
        GameEntity* entity = entities[i];
        
        entity->updateComponentOfType(GameComponentType::Render);
    }
    
    application_context_.flush();
}