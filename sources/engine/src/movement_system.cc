#include "movement_system.h"
#include "logging/log.h"

const glm::vec3 bounce::MovementSystem::yaw_axis_{0.0f, 1.0f, 0.0f};
const glm::vec3 bounce::MovementSystem::pitch_axis_{1.0f, 0.0f, 0.0f};
const glm::vec3 bounce::MovementSystem::roll_axis_{0.0f, 0.0f, 1.0f};

bounce::MovementSystem::MovementSystem(ObjectCache<GameEntity>& game_entities, GameComponentManager& component_manager)
: game_entities_(game_entities), component_manager_(component_manager)
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
    for (GameEntity& entity : game_entities_) {
        GameComponentHandle component_handle = entity.GetComponentOfType(BODY_COMPONENT);

        if (component_handle.is_valid()) {
            BodyComponent& component = component_manager_.ResolveHandleAs<BodyComponent>(component_handle);
            
            UpdateRotation(component, delta_time);
            UpdatePosition(component, delta_time);
            
            PositionChangedMessage message(component.position());
            entity.HandleMessage(message);
        }
    }
}

void bounce::MovementSystem::UpdateRotation(BodyComponent& component, float delta_time)
{
    float delta_speed = component.rotation_acceleration() * delta_time;
    
    float pitch = UpdateSpeed(delta_speed, component.pitch_acceleration_direction(), component.pitch_speed(), component.max_speed());
    float yaw = UpdateSpeed(delta_speed, component.yaw_acceleration_direction(), component.yaw_speed(), component.max_speed());
    float roll = UpdateSpeed(delta_speed, component.roll_acceleration_direction(), component.roll_speed(), component.max_speed());
    
    component.pitch_speed(pitch);
    component.yaw_speed(yaw);
    component.roll_speed(roll);
        
    glm::quat pitch_rotation = glm::angleAxis(pitch, pitch_axis_);
    glm::quat yaw_rotation = glm::angleAxis(yaw, yaw_axis_);
    glm::quat roll_rotation = glm::angleAxis(roll, roll_axis_);
    
    const glm::quat& orientation = component.orientation();
    glm::quat rot = orientation * pitch_rotation * yaw_rotation * roll_rotation;
    
    component.orientation(rot);
}

void bounce::MovementSystem::UpdatePosition(BodyComponent& component, float delta_time)
{
    glm::vec3 delta_position = component.acceleration() * (delta_time / 1000);
    
    glm::vec3 position = component.position() + delta_position;
    
    component.position(position);
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
