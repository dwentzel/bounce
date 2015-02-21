#include "keyboard_control_strategy.h"

bounce::KeyboardControlStrategy::KeyboardControlStrategy(const KeyboardState& keyboard_state)
: ControlStrategy(),
keyboard_state_(keyboard_state),
yaw_acceleration_(0),
pitch_acceleration_(0),
roll_acceleration_(0)
{
    
}

bounce::KeyboardControlStrategy::KeyboardControlStrategy(KeyboardControlStrategy&& other) NOEXCEPT
: ControlStrategy(std::move(other)), keyboard_state_(std::move(other.keyboard_state_))
{
    
}

void bounce::KeyboardControlStrategy::Update()
{
    yaw_acceleration_ = 0;
    pitch_acceleration_ = 0;
    roll_acceleration_ = 0;
    
    if (keyboard_state_.IsDown(KEY_Q)) {
        ++yaw_acceleration_;
    }
    
    if (keyboard_state_.IsDown(KEY_E)) {
        --yaw_acceleration_;
    }
    
    if (keyboard_state_.IsDown(KEY_W)) {
        --pitch_acceleration_;
    }
    
    if (keyboard_state_.IsDown(KEY_S)) {
        ++pitch_acceleration_;
    }
    
    if (keyboard_state_.IsDown(KEY_A)) {
        ++roll_acceleration_;
    }
    
    if (keyboard_state_.IsDown(KEY_D)) {
        --roll_acceleration_;
    }
}

std::unique_ptr<bounce::Message> bounce::KeyboardControlStrategy::CreateMessage() const
{
    return std::unique_ptr<Message>(new AccelerationChangedMessage(yaw_acceleration_, pitch_acceleration_, roll_acceleration_, glm::vec3(0.0f)));
}

int bounce::KeyboardControlStrategy::yaw_acceleration() const
{
    return yaw_acceleration_;
}

int bounce::KeyboardControlStrategy::pitch_acceleration() const
{
    return pitch_acceleration_;
}

int bounce::KeyboardControlStrategy::roll_acceleration() const
{
    return roll_acceleration_;
}
