#include "object_manager.h"

bounce::ObjectManager bounce::ObjectManager::instance_;

const bounce::ObjectCache<bounce::GameEntity>& bounce::ObjectManager::game_entities() const
{
    return game_entities_;
}

bounce::BodyComponentCache& bounce::ObjectManager::body_components()
{
    return body_components_;
}

const bounce::BodyComponentCache& bounce::ObjectManager::body_components() const
{
    return body_components_;
}

bounce::ControlComponentCache& bounce::ObjectManager::control_components()
{
    return control_components_;
}

const bounce::ControlComponentCache& bounce::ObjectManager::control_components() const
{
    return control_components_;
}

bounce::AiComponentCache& bounce::ObjectManager::ai_components()
{
    return ai_components_;
}

const bounce::AiComponentCache& bounce::ObjectManager::ai_components() const
{
    return ai_components_;
}

const bounce::RenderComponentCache& bounce::ObjectManager::render_components() const
{
    return render_components_;
}

const bounce::PointLightComponentCache& bounce::ObjectManager::point_light_components() const
{
    return point_light_components_;
}


bounce::GameEntityHandle bounce::ObjectManager::GenerateGameEntity()
{
    unsigned int index = game_entities_.GenerateObject();
    return GameEntityHandle(GAME_ENTITY_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateBodyComponent(GameEntityHandle owner)
{
    unsigned int index = body_components_.GenerateObject(owner);
    return GameComponentHandle(BODY_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state)
{
    unsigned int index = control_components_.GenerateObject(owner, keyboard_state);
    return GameComponentHandle(CONTROL_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateAiComponent(GameEntityHandle owner)
{
    unsigned int index = ai_components_.GenerateObject(owner);
    return GameComponentHandle(AI_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateRenderComponent(GameEntityHandle owner, unsigned int model_handle)
{
    unsigned int index = render_components_.GenerateObject(owner, model_handle);
    return GameComponentHandle(RENDER_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GeneratePointLightComponent(GameEntityHandle owner)
{
    unsigned int index = point_light_components_.GenerateObject(owner);
    return GameComponentHandle(POINT_LIGHT_COMPONENT_TYPE, index);
}

//bounce::GameEntity& bounce::ObjectManager::GetGameEntity(unsigned int handle)
//{
//    return game_entities_.GetObject(handle);
//}
//
//bounce::BodyComponent& bounce::ObjectManager::GetBodyComponent(unsigned int handle)
//{
//    return body_components_.GetObject(handle);
//}
//
//bounce::RenderComponent& bounce::ObjectManager::GetRenderComponent(unsigned int handle)
//{
//    return render_components_.GetObject(handle);
//}
//
//bounce::PointLightComponent& bounce::ObjectManager::GetPointLightComponent(unsigned int handle)
//{
//    return point_light_components_.GetObject(handle);
//}