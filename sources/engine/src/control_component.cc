#include "control_component.h"

bounce::ControlComponent bounce::ControlComponent::Create(GameEntityHandle owner, const bounce::KeyboardState& keyboard_state)
{
    return ControlComponent(owner, keyboard_state);
}

bounce::ControlComponent::ControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state)
: GameComponent(CONTROL_COMPONENT, owner), keyboard_state_(keyboard_state)
{
    
}

bounce::ControlComponent::ControlComponent(ControlComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)), keyboard_state_(std::move(other.keyboard_state_))
{

}

void bounce::ControlComponent::Startup() {
    
}

void bounce::ControlComponent::Shutdown() {
    
}

void bounce::ControlComponent::Update() {
    int yaw_acceleration = 0;
    int pitch_acceleration = 0;
    int roll_acceleration = 0;
    
    if (keyboard_state_.IsDown(KEY_Q)) {
        ++yaw_acceleration;
    }
    
    if (keyboard_state_.IsDown(KEY_E)) {
        --yaw_acceleration;
    }
    
    if (keyboard_state_.IsDown(KEY_W)) {
        --pitch_acceleration;
    }
    
    if (keyboard_state_.IsDown(KEY_S)) {
        ++pitch_acceleration;
    }
    
    if (keyboard_state_.IsDown(KEY_A)) {
        ++roll_acceleration;
    }
    
    if (keyboard_state_.IsDown(KEY_D)) {
        --roll_acceleration;
    }
    
//    if (yaw_acceleration != 0 || pitch_acceleration != 0 || roll_acceleration != 0) {
    AccelerationChangedMessage message(yaw_acceleration, pitch_acceleration, roll_acceleration, glm::vec3(0.0f));
    
        SendMessage(message);
//    }
}
