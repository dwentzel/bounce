#include "game_component.h"

#include "object_manager.h"

bounce::GameComponent::GameComponent(GameComponentType component_type, GameEntityHandle owner)
: component_type_(component_type), owner_(owner)
{
    
}

bounce::GameComponent::~GameComponent()
{
    
}

void bounce::GameComponent::SendMessage(const bounce::Message& message) const
{
    owner_.Resolve().HandleMessage(message);
}