#include "ai_orbit_strategy.h"

bounce::AiOrbitStrategy::AiOrbitStrategy(float radius, int direction, const glm::vec3& center)
: radius_(radius), direction_(direction), center_(center)
{
    
}

bounce::AiOrbitStrategy::~AiOrbitStrategy()
{

}

void bounce::AiOrbitStrategy::Update(const AiComponent& owner)
{
    glm::vec3 v = position_ - center_;
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm:: vec3 normal = glm::normalize(glm::cross(v, axis));
    
    AccelerationChangedMessage message(0.0f, 0.0f, 0.0f, normal);
    SendMessage(owner, message);
}

void bounce::AiOrbitStrategy::HandleMessage(const bounce::Message& message)
{
    if (message.message_type() == POSITION_CHANGED_MESSAGE) {
        const PositionChangedMessage& position_changed_message = static_cast<const PositionChangedMessage&>(message);
        position_ = position_changed_message.position();
    }
}

void bounce::AiOrbitStrategy::position(const glm::vec3& value)
{
    position_ = value;
}