#include "game_component_manager.h"

bounce::GameComponentManager bounce::GameComponentManager::instance_;

bounce::GameComponentManager& bounce::GameComponentManager::instance()
{
    return instance_;
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

bounce::GameComponentHandle bounce::GameComponentManager::GenerateBodyComponent(GameEntityHandle owner)
{
    unsigned int index = body_components_.GenerateObject(owner);
    return GameComponentHandle(BODY_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state)
{
    unsigned int index = control_components_.GenerateObject(owner, keyboard_state);
    return GameComponentHandle(CONTROL_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateAiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy)
{
    unsigned int index = ai_components_.GenerateObject(owner, std::move(ai_strategy));
    return GameComponentHandle(AI_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GenerateRenderComponent(GameEntityHandle owner, unsigned int model_handle)
{
    unsigned int index = render_components_.GenerateObject(owner, model_handle);
    return GameComponentHandle(RENDER_COMPONENT, index);
}

bounce::GameComponentHandle bounce::GameComponentManager::GeneratePointLightComponent(GameEntityHandle owner)
{
    unsigned int index = point_light_components_.GenerateObject(owner);
    return GameComponentHandle(POINT_LIGHT_COMPONENT, index);
}
