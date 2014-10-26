#include "movement_component.h"
#include "bounce_gl.h"

#include <cstdio>

float bounce::MovementComponent::UpdateSpeed(float delta_speed, int acceleration_direction, float speed) {
    float new_speed = speed;
    float max_speed = owner()->max_speed();
    
    
    if (acceleration_direction > 0) {
        if (new_speed < max_speed) {
            new_speed += delta_speed;
            
            if (new_speed > max_speed) {
                new_speed = max_speed;
            }
        }
    }
    else if (acceleration_direction < 0) {
        if (new_speed > -max_speed) {
            new_speed -= delta_speed;
            
            if (new_speed < -max_speed) {
                new_speed = -max_speed;
            }
        }
    }
    else {
        if (new_speed > 0) {
            new_speed -= delta_speed;
        }
        else if (new_speed < 0) {
            new_speed += delta_speed;
        }
    }
    
    if (std::abs(new_speed) < delta_speed) {
        if (acceleration_direction == 0) {
            new_speed = 0.0f;
        }
    }
    
    return new_speed;
}

void bounce::MovementComponent::Startup() {
    
}

void bounce::MovementComponent::Shutdown() {
    
}

void bounce::MovementComponent::Update() {
    GameEntity* owner = this->owner();
    
    float delta_time = timer_.frame_time();
    float delta_speed = owner->rotation_acceleration() * delta_time;
    
    owner->horizontal_speed(UpdateSpeed(delta_speed, owner->horizontal_acceleration_direction(), owner->horizontal_speed()));
    owner->vertical_speed(UpdateSpeed(delta_speed, owner->vertical_acceleration_direction(), owner->vertical_speed()));
    
    float horizontal_angle = owner->horizontal_angle();
    float vertical_angle = owner->vertical_angle();
    
    horizontal_angle += owner->horizontal_speed();
    vertical_angle += owner->vertical_speed();
    
    if (vertical_angle > PI2) {
        vertical_angle -= PI2;
    }
    else if (vertical_angle < 0.0f) {
        vertical_angle += PI2;
    }
    
    if (horizontal_angle > PI2) {
        horizontal_angle -= PI2;
    }
    else if (horizontal_angle < 0.0f) {
        horizontal_angle += PI2;
    }
    
    glm::quat horizontal = glm::angleAxis(horizontal_angle, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::quat vertical = glm::angleAxis(vertical_angle, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
    glm::quat rot = vertical * horizontal;
    
    owner->horizontal_angle(horizontal_angle);
    owner->vertical_angle(vertical_angle);
    owner->orientation(rot);
}