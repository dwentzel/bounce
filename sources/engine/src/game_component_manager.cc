#include "game_component_manager.h"

bounce::GameComponentManager::GameComponentManager()
{

}

bounce::BodyComponentCache& bounce::GameComponentManager::body_components()
{
    return body_components_;
}

const bounce::BodyComponentCache& bounce::GameComponentManager::body_components() const
{
    return body_components_;
}

bounce::ControlComponentCache& bounce::GameComponentManager::control_components()
{
    return control_components_;
}

const bounce::ControlComponentCache& bounce::GameComponentManager::control_components() const
{
    return control_components_;
}

bounce::AiComponentCache& bounce::GameComponentManager::ai_components()
{
    return ai_components_;
}

const bounce::AiComponentCache& bounce::GameComponentManager::ai_components() const
{
    return ai_components_;
}

const bounce::RenderComponentCache& bounce::GameComponentManager::render_components() const
{
    return render_components_;
}

const bounce::PointLightComponentCache& bounce::GameComponentManager::point_light_components() const
{
    return point_light_components_;
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateBodyComponent()
{
    unsigned int index = body_components_.GenerateObject();
    return GameComponentHandle(BODY_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateControlComponent(std::unique_ptr<ControlStrategy> control_strategy)
{
    unsigned int index = control_components_.GenerateObject(std::move(control_strategy));
    return GameComponentHandle(CONTROL_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateAiComponent(std::unique_ptr<AiStrategy> ai_strategy)
{
    unsigned int index = ai_components_.GenerateObject(std::move(ai_strategy));
    return GameComponentHandle(AI_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateRenderComponent(unsigned int model_handle)
{
    unsigned int index = render_components_.GenerateObject(model_handle);
    return GameComponentHandle(RENDER_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GeneratePointLightComponent()
{
    unsigned int index = point_light_components_.GenerateObject();
    return GameComponentHandle(POINT_LIGHT_COMPONENT, index);
}
