#include "body_component.h"
#include "object_manager.h"
#include "game_entity.h"

bounce::BodyComponent::BodyComponent(GameEntityHandle owner)
: GameComponent(BODY_COMPONENT, owner),
  yaw_acceleration_direction_(0), pitch_acceleration_direction_(0), roll_acceleration_direction_(0),
  rotation_acceleration_(0.0002f), max_speed_(0.1f), yaw_speed_(0.0f), pitch_speed_(0.0f), roll_speed_(0.0f),
  orientation_(1.0f, 0.0f, 0.0f, 0.0f), acceleration_(0.0f), velocity_(0.0f), position_(0.0f)
{
    
}

bounce::BodyComponent bounce::BodyComponent::Create(GameEntityHandle owner)
{
    return BodyComponent(owner);
}


void bounce::BodyComponent::Startup()
{
    PositionChangedMessage message = PositionChangedMessage(position_);
    SendMessage(message);
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