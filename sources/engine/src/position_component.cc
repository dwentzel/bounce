#include "position_component.h"

bounce::PositionComponent::PositionComponent(const glm::vec3& position)
: GameComponent(POSITION_COMPONENT), position_(position)
{
    
}

void bounce::PositionComponent::Startup()
{
    PositionChangedMessage message(position_);
    
    owner()->HandleMessage(message);
}

void bounce::PositionComponent::Shutdown()
{
    
}

void bounce::PositionComponent::Update()
{
    
}
