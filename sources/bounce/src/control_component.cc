#include "control_component.h"
#include "bounce_gl.h"

void bounce::ControlComponent::Startup() {
    
}

void bounce::ControlComponent::Shutdown() {
    
}

void bounce::ControlComponent::Update() {
    int horizontal_acceleration = 0;
    int vertical_acceleration = 0;
    
    if (keyboard_state_.IsDown(Key::A)) {
        --horizontal_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::D)) {
        ++horizontal_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::W)) {
        ++vertical_acceleration;
    }
    
    if (keyboard_state_.IsDown(Key::S)) {
        --vertical_acceleration;
    }
    
    GameEntity* owner = this->owner();
    
    owner->horizontal_acceleration_direction(horizontal_acceleration);
    owner->vertical_acceleration_direction(vertical_acceleration);

}