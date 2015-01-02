#include "control_component.h"

bounce::ControlComponent bounce::ControlComponent::Create(const bounce::KeyboardState& keyboard_state)
{
    return ControlComponent(keyboard_state);
}

bounce::ControlComponent::ControlComponent(const KeyboardState& keyboard_state)
: GameComponent(CONTROL_COMPONENT),
  keyboard_state_(keyboard_state),
  yaw_acceleration_(0),
  pitch_acceleration_(0),
  roll_acceleration_(0)
{
    
}

bounce::ControlComponent::ControlComponent(ControlComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)), keyboard_state_(std::move(other.keyboard_state_))
{

}

void bounce::ControlComponent::Startup()
{
    
}

void bounce::ControlComponent::Shutdown()
{
    
}

void bounce::ControlComponent::Update()
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
    
//    if (yaw_acceleration != 0 || pitch_acceleration != 0 || roll_acceleration != 0) {
//    AccelerationChangedMessage message(yaw_acceleration, pitch_acceleration, roll_acceleration, glm::vec3(0.0f));
//    
//        SendMessage(message);
//    }
}

int bounce::ControlComponent::yaw_acceleration() const
{
    return yaw_acceleration_;
}

int bounce::ControlComponent::pitch_acceleration() const
{
    return pitch_acceleration_;
}

int bounce::ControlComponent::roll_acceleration() const
{
    return roll_acceleration_;
}
