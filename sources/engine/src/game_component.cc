#include "game_component.h"

#include <algorithm>

bounce::GameComponent::GameComponent(GameComponentType component_type)
: component_type_(component_type)
{
    
}

//bounce::GameComponent::GameComponent(const GameComponent& other)
//    : component_type_(other.component_type_), owner_(other.owner_)
//{
//
//}

bounce::GameComponent::GameComponent(GameComponent&& other) NOEXCEPT
    : component_type_(std::move(other.component_type_))
{

}

bounce::GameComponent::~GameComponent()
{
    
}
