#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "contrib/enable_clang_warnings.h"

#include "logging/log.h"

#include "render_system.h"
#include "game_entity.h"
#include "render_component.h"
#include "point_light_component.h"
#include "object_manager_handle.h"

bounce::RenderSystem::RenderSystem(const ApplicationContext& application_context,
                                   const WindowContext& window_context,
                                   GameEntityCache& game_entity_cache,
                                   GameComponentManager& component_manager,
                                   OpenGLRenderer& renderer)
: application_context_(application_context),
  window_context_(window_context),
  game_entity_cache_(game_entity_cache),
  component_manager_(component_manager),
  renderer_(renderer)
{
    
}

bounce::RenderSystem::~RenderSystem()
{
    
}

void bounce::RenderSystem::Startup()
{
    renderer_.Startup();
    renderer_.Resize(window_context_.width(), window_context_.height());
}

void bounce::RenderSystem::Shutdown() {
    renderer_.Shutdown();
}

namespace {
    
    float initialFoV = 45.0f;
}


void bounce::RenderSystem::Update(float delta_time)
{    
    glm::vec3 camera_position(2.0f, 3.0f, 5.0f);
    float fov = initialFoV;
    
    glm::mat4 projection_matrix = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view_matrix = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 vp_matrix = projection_matrix * view_matrix;
    
    renderer_.BeginGeometryPass();
    renderer_.SetViewMatrix(view_matrix);
    renderer_.SetVPMatrix(vp_matrix);
    
    for (GameEntity& entity : game_entity_cache_) {
        GameComponentHandle component_handle = entity.GetComponentOfType(RENDER_COMPONENT);
        if (!component_handle.invalid()) {
            const RenderComponent& render_component = component_manager_.ResolveHandleAs<RenderComponent>(component_handle);
            
            glm::mat4 world_matrix = render_component.model_matrix();
            glm::mat4 wvp_matrix = vp_matrix * world_matrix;
            
            renderer_.SetWVPMatrix(wvp_matrix);
            renderer_.SetWorldMatrix(world_matrix);
            
            renderer_.RenderModel(render_component.model_handle());
        }
    }
    
    renderer_.EndGeometryPass();
    
    renderer_.BeginLightPasses();
    
    renderer_.BeginPointLightsPass();
    
    for (GameEntity& entity : game_entity_cache_) {
        GameComponentHandle component_handle = entity.GetComponentOfType(POINT_LIGHT_COMPONENT);
        if (!component_handle.invalid()) {
            const PointLightComponent& point_light_component_ = component_manager_.ResolveHandleAs<PointLightComponent>(component_handle);
            
            renderer_.RenderPointLight(point_light_component_.light());
        }
    }
    
    renderer_.EndPointLighsPass();
    renderer_.RunDirectionalLightPass();
    
    application_context_.Flush();
}

void bounce::RenderSystem::RenderModel(unsigned int model_handle)
{
    renderer_.RenderModel(model_handle);
}
