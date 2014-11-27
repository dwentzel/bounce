#include "control_component.h"
#include "object_manager.h"

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
    
    
    GameEntity& owner = this->owner().Resolve();
    AccelerationChangedMessage message(yaw_acceleration, pitch_acceleration, roll_acceleration);
    
    owner.HandleMessage(message);
    
//    owner->yaw_acceleration_direction(yaw_acceleration);
//    owner->pitch_acceleration_direction(pitch_acceleration);
//    owner->roll_acceleration_direction(roll_acceleration);
}