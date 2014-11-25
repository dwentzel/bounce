#include "movement_system.h"

bounce::MovementSystem::MovementSystem(BodyComponentCache& body_components)
: body_components_(body_components)
{
    
}

void bounce::MovementSystem::Startup()
{
    
}

void bounce::MovementSystem::Shutdown()
{
    
}

void bounce::MovementSystem::Update(float delta_time)
{
    for (BodyComponentCache::iterator handle = body_components_.begin();
         handle != body_components_.end(); ++handle) {
        
        BodyComponent& component = *handle;
        
        float delta_speed = component.rotation_acceleration() * delta_time;
        
        component.yaw_speed(UpdateSpeed(delta_speed, component.yaw_acceleration_direction(), component.yaw_speed(), component.max_speed()));
        component.pitch_speed(UpdateSpeed(delta_speed, component.pitch_acceleration_direction(), component.pitch_speed(), component.max_speed()));
        component.roll_speed(UpdateSpeed(delta_speed, component.roll_acceleration_direction(), component.roll_speed(), component.max_speed()));
        
        float yaw = component.yaw_speed();
        float pitch = component.pitch_speed();
        float roll = component.roll_speed();
        
        glm::quat orientation = component.orientation();
        
        glm::vec3 yaw_axis(0.0f, 1.0f, 0.0f);
        glm::vec3 pitch_axis(1.0f, 0.0f, 0.0f);
        glm::vec3 roll_axis(0.0f, 0.0f, 1.0f);
        
        glm::quat pitch_rotation = glm::angleAxis(pitch, pitch_axis);
        glm::quat yaw_rotation = glm::angleAxis(yaw, yaw_axis);
        glm::quat roll_rotation = glm::angleAxis(roll, roll_axis);
        
        glm::quat rot = orientation * pitch_rotation * yaw_rotation * roll_rotation;
        
        component.orientation(rot);
    }
}

float bounce::MovementSystem::UpdateSpeed(float delta_speed, float acceleration_direction, float speed, float max_speed) const
{
    float new_speed = speed;
    
    if (acceleration_direction > 0.0f) {
        if (new_speed < max_speed) {
            new_speed += delta_speed;
            
            if (new_speed > max_speed) {
                new_speed = max_speed;
            }
        }
    }
    else if (acceleration_direction < 0.0f) {
        if (new_speed > -max_speed) {
            new_speed -= delta_speed;
            
            if (new_speed < -max_speed) {
                new_speed = -max_speed;
            }
        }
    }
    else {
        if (new_speed > 0.0f) {
            new_speed -= delta_speed;
        }
        else if (new_speed < 0.0f) {
            new_speed += delta_speed;
        }
    }
    
    if (std::abs(new_speed) < delta_speed) {
        if (acceleration_direction - 0.0f < 0.0001f) {
            new_speed = 0.0f;
        }
    }
    
    return new_speed;
}