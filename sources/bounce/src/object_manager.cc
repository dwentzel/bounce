#include "object_manager.h"

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
    return GameEntityHandle(*this, GAME_ENTITY_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateBodyComponent()
{
    unsigned int index = body_components_.GenerateObject();
    return GameComponentHandle(*this, BODY_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GenerateRenderComponent(unsigned int model_handle)
{
    unsigned int index = render_components_.GenerateObject(model_handle);
    return GameComponentHandle(*this, RENDER_COMPONENT_TYPE, index);
}

bounce::GameComponentHandle bounce::ObjectManager::GeneratePointLightComponent()
{
    unsigned int index = point_light_components_.GenerateObject();
    return GameComponentHandle(*this, POINT_LIGHT_COMPONENT_TYPE, index);
}

bounce::GameEntity& bounce::ObjectManager::GetGameEntity(unsigned int handle)
{
    return game_entities_.GetObject(handle);
}

bounce::BodyComponent& bounce::ObjectManager::GetBodyComponent(unsigned int handle)
{
    return body_components_.GetObject(handle);
}

bounce::RenderComponent& bounce::ObjectManager::GetRenderComponent(unsigned int handle)
{
    return render_components_.GetObject(handle);
}

bounce::PointLightComponent& bounce::ObjectManager::GetPointLightComponent(unsigned int handle)
{
    return point_light_components_.GetObject(handle);
}