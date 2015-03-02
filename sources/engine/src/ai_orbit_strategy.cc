#include "ai_orbit_strategy.h"

bounce::AiOrbitStrategy::AiOrbitStrategy(float radius, int direction, const glm::vec3& center)
: radius_(radius), direction_(direction), center_(center)
{
    
}

bounce::AiOrbitStrategy::~AiOrbitStrategy()
{

}

void bounce::AiOrbitStrategy::Update()
{
//    glm::vec3 v = position_ - center_;
//    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cross = glm::cross(position_, center_);
    if (cross == glm::vec3(0.0f)) {
        normal_ = glm::vec3(0);
    }
    else {
        normal_ = glm::normalize(cross);
    }
//    normal_ = glm::normalize(glm::cross(v, axis));
    assert(!std::isnan(normal_.x));
    assert(!std::isnan(normal_.y));
    assert(!std::isnan(normal_.z));
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
