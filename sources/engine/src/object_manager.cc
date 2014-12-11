#include "object_manager.h"

bounce::EntityManager bounce::EntityManager::instance_;

bounce::EntityManager& bounce::EntityManager::instance()
{
    return instance_;
}

bounce::GameEntityCache& bounce::EntityManager::game_entities()
{
    return game_entities_;
}

const bounce::GameEntityCache& bounce::EntityManager::game_entities() const
{
    return game_entities_;
}

bounce::GameEntityHandle bounce::EntityManager::GenerateGameEntity()
{
    unsigned int index = game_entities_.GenerateObject();
    return GameEntityHandle(0, index);
}


bounce::ComponentManager bounce::ComponentManager::instance_;

bounce::ComponentManager& bounce::ComponentManager::instance()
{
    return instance_;
}

bounce::BodyComponentCache& bounce::ComponentManager::body_components()
{
    return body_components_;
}

const bounce::BodyComponentCache& bounce::ComponentManager::body_components() const
{
    return body_components_;
}

bounce::ControlComponentCache& bounce::ComponentManager::control_components()
{
    return control_components_;
}

const bounce::ControlComponentCache& bounce::ComponentManager::control_components() const
{
    return control_components_;
}

bounce::AiComponentCache& bounce::ComponentManager::ai_components()
{
    return ai_components_;
}

const bounce::AiComponentCache& bounce::ComponentManager::ai_components() const
{
    return ai_components_;
}

const bounce::RenderComponentCache& bounce::ComponentManager::render_components() const
{
    return render_components_;
}

const bounce::PointLightComponentCache& bounce::ComponentManager::point_light_components() const
{
    return point_light_components_;
}


//bounce::GameEntityHandle bounce::ObjectManager::GenerateGameEntity()
//{
//    unsigned int index = game_entities_.GenerateObject();
//    return GameEntityHandle(GAME_ENTITY_TYPE, index);
//}

bounce::GameComponentHandle bounce::ComponentManager::GenerateBodyComponent(GameEntityHandle owner)
{
    unsigned int index = body_components_.GenerateObject(owner);
    return GameComponentHandle(BODY_COMPONENT, index);
}

bounce::GameComponentHandle bounce::ComponentManager::GenerateControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state)
{
    unsigned int index = control_components_.GenerateObject(owner, keyboard_state);
    return GameComponentHandle(CONTROL_COMPONENT, index);
}

bounce::GameComponentHandle bounce::ComponentManager::GenerateAiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy)
{
    unsigned int index = ai_components_.GenerateObject(owner, std::move(ai_strategy));
    return GameComponentHandle(AI_COMPONENT, index);
}

bounce::GameComponentHandle bounce::ComponentManager::GenerateRenderComponent(GameEntityHandle owner, unsigned int model_handle)
{
    unsigned int index = render_components_.GenerateObject(owner, model_handle);
    return GameComponentHandle(RENDER_COMPONENT, index);
}

bounce::GameComponentHandle bounce::ComponentManager::GeneratePointLightComponent(GameEntityHandle owner)
{
    unsigned int index = point_light_components_.GenerateObject(owner);
    return GameComponentHandle(POINT_LIGHT_COMPONENT, index);
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
