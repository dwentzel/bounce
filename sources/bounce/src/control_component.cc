#include "control_component.h"
#include "bounce_gl.h"

void bounce::ControlComponent::Startup() {
    
}

void bounce::ControlComponent::Shutdown() {
    
}

void bounce::ControlComponent::Update() {
    int yaw_acceleration = 0;
    int pitch_acceleration = 0;
    int roll_acceleration = 0;
    
    if (keyboard_state_.IsDown(Key::Q)) {
        ++yaw_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::E)) {
        --yaw_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::W)) {
        --pitch_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::S)) {
        ++pitch_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::A)) {
        ++roll_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::D)) {
        --roll_acceleration;
    }
    
    
    GameEntity* owner = this->owner();
    
    owner->yaw_acceleration_direction(yaw_acceleration);
    owner->pitch_acceleration_direction(pitch_acceleration);
    owner->roll_acceleration_direction(roll_acceleration);
}