#include "body_component.h"
#include "game_entity.h"

bounce::BodyComponent bounce::BodyComponent::Create()
{
    return BodyComponent();
}

bounce::BodyComponent::BodyComponent()
: GameComponent(BODY_COMPONENT),
  yaw_acceleration_direction_(0),
  pitch_acceleration_direction_(0),
  roll_acceleration_direction_(0),
  rotation_acceleration_(0.0002f),
  max_speed_(0.1f),
  yaw_speed_(0.0f),
  pitch_speed_(0.0f),
  roll_speed_(0.0f),
  orientation_(1.0f, 0.0f, 0.0f, 0.0f),
  acceleration_(0.0f),
  velocity_(0.0f),
  position_(0.0f)
{
    
}

bounce::BodyComponent::BodyComponent(BodyComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)),
    yaw_acceleration_direction_(std::move(other.yaw_acceleration_direction_)),
    pitch_acceleration_direction_(std::move(other.pitch_acceleration_direction_)),
    roll_acceleration_direction_(std::move(other.roll_acceleration_direction_)),
    rotation_acceleration_(std::move(other.rotation_acceleration_)),
    max_speed_(std::move(other.max_speed_)),
    yaw_speed_(std::move(other.yaw_speed_)),
    pitch_speed_(std::move(other.pitch_speed_)),
    roll_speed_(std::move(other.roll_speed_)),
    orientation_(std::move(other.orientation_)),
    acceleration_(std::move(other.acceleration_)),
    velocity_(std::move(other.velocity_)),
    position_(std::move(other.position_))
{

}


void bounce::BodyComponent::Startup()
{

}

void bounce::BodyComponent::Shutdown()
{
    
}

void bounce::BodyComponent::Update()
{
    
}

void bounce::BodyComponent::HandleMessage(const bounce::Message& message)
{
    if (message.message_type() == ACCELERATION_CHANGED_MESSAGE) {
        const AccelerationChangedMessage& acceleration_changed_message = static_cast<const AccelerationChangedMessage&>(message);

        yaw_acceleration_direction_ = acceleration_changed_message.yaw();
        pitch_acceleration_direction_ = acceleration_changed_message.pitch();
        roll_acceleration_direction_ = acceleration_changed_message.roll();
        
        acceleration_ = acceleration_changed_message.direction();
    }
        
}

void bounce::BodyComponent::position(const glm::vec3& position)
{
    position_ = position;
}

glm::mat4 bounce::BodyComponent::world_matrix() const
{
    return glm::mat4_cast(orientation_);
}
