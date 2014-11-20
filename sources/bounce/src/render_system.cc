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
    
    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));
    
    glm::vec3 camera_position(2.0f, 3.0f, 5.0f);
    float fov = initialFoV;
    
    glm::mat4 projection_matrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view_matrix = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 world_matrix = glm::mat4(1.0f);
    glm::mat4 wvp_matrix = projection_matrix * view_matrix * world_matrix;


    renderer_.BeginFrame();
    
    renderer_.SetViewMatrix(view_matrix);
    renderer_.SetWorldMatrix(world_matrix);
    renderer_.SetWVPMatrix(wvp_matrix);
    
    const GameEntityList& entities = world_manager_.entities();
    
    for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
        GameEntity* entity = *i;
        
        glm::mat4 model_matrix = glm::toMat4(entity->orientation());
        //        glm::mat4 mwvp_matrix = projection_matrix * view_matrix * model_matrix;
        glm::mat4 mwvp_matrix = wvp_matrix * model_matrix;
        
        
        renderer_.SetMWVPMatrix(mwvp_matrix);
        renderer_.SetModelMatrix(model_matrix);
        
//        renderer_.RenderModel(entity->model_handle)
        entity->UpdateComponentOfType(RENDER_COMPONENT);
    }
    
    renderer_.EndFrame();
    
    application_context_.Flush();
}

void bounce::RenderSystem::AddModel(unsigned int model_handle)
{
    model_handles_.push_back(model_handle);
    renderer_.AddModel(model_handle);
}

void bounce::RenderSystem::RemoveModel(unsigned int model_handle)
{
    LOG_ERROR << "bounce::RenderSystem::RemoveModel not implemented" << std::endl;
}

void bounce::RenderSystem::RenderModel(unsigned int model_handle)
{
    renderer_.RenderModel(model_handle);
}
