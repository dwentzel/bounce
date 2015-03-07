#include "ai_orbit_strategy.h"

#include "framework/contracts.h"

bounce::AiOrbitStrategy::AiOrbitStrategy(float radius, int direction, const glm::vec3& center)
: radius_(radius), direction_(direction), center_(center)
{
    
}

bounce::AiOrbitStrategy::~AiOrbitStrategy()
{

}

void bounce::AiOrbitStrategy::Update()
{
    CONTRACT_ENSURES(!std::isnan(normal_.x));
    CONTRACT_ENSURES(!std::isnan(normal_.y));
    CONTRACT_ENSURES(!std::isnan(normal_.z));
    
    glm::vec3 cross = glm::cross(position_, center_);
    if (cross == glm::vec3(0.0f)) {
        normal_ = glm::vec3(0);
    }
    else {
        normal_ = glm::normalize(cross);
    }
}

void bounce::AiOrbitStrategy::HandleMessage(const bounce::Message& message)
{
    if (message.message_type() == POSITION_CHANGED_MESSAGE) {
        const PositionChangedMessage& position_changed_message = static_cast<const PositionChangedMessage&>(message);
        position_ = position_changed_message.position();
    }
}

std::unique_ptr<bounce::Message> bounce::AiOrbitStrategy::CreateMessage() const
{
    return std::unique_ptr<Message>(new AccelerationChangedMessage(0.0f, 0.0f, 0.0f, normal_));
}

void bounce::AiOrbitStrategy::position(const glm::vec3& value)
{
    position_ = value;
}
