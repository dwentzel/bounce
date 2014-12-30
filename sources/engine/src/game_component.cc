#include "game_component.h"

#include <algorithm>

bounce::GameComponent::GameComponent(GameComponentType component_type, GameEntityHandle owner)
: component_type_(component_type), owner_(owner)
{
    
}

//bounce::GameComponent::GameComponent(const GameComponent& other)
//    : component_type_(other.component_type_), owner_(other.owner_)
//{
//
//}

bounce::GameComponent::GameComponent(GameComponent&& other)
    : component_type_(std::move(other.component_type_)), owner_(std::move(other.owner_))
{

}

bounce::GameComponent::~GameComponent()
{
    
}

void bounce::GameComponent::SendMessage(const bounce::Message& message) const
{
    owner_.Resolve().HandleMessage(message);
}

bounce::GameComponentHandle bounce::GameEntity::GetComponentOfType(GameComponentType type)
{
    component_iterator iter = std::find_if(game_components_.begin(), game_components_.end(), [type](const GameComponentHandle& handle) {
        return handle.type() == type;
    });
    
    if (iter != game_components_.end()) {
        return *iter;
    }
    else {
        return GameComponentHandle::invalid_handle;
    }
}
