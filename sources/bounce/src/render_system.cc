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
}
