#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

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

namespace {
    glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
        start = glm::normalize(start);
        dest = glm::normalize(dest);
        
        float cosTheta = glm::dot(start, dest);
        glm::vec3 rotationAxis;
        
//        if (cosTheta < -1 + 0.001f){
//            // special case when vectors in opposite directions:
//            // there is no "ideal" rotation axis
//            // So guess one; any will do as long as it's perpendicular to start
//            rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
//            if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
//                rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
//            
//            rotationAxis = glm::normalize(rotationAxis);
//            return glm::angleAxis(bounce::PI, rotationAxis);
//        }
        
        rotationAxis = glm::cross(start, dest);
        
        float s = sqrt( (1+cosTheta)*2 );
        float invs = 1 / s;
        
        return glm::quat(
                    s * 0.5f,
                    rotationAxis.x * invs,
                    rotationAxis.y * invs,
                    rotationAxis.z * invs
                    );
        
    }
    
    void PrintVector(const glm::vec3& vector) {
        
        std::fprintf(stdout, "vector: %f, %f, %f\n", vector.x, vector.y, vector.z);
        
    }
    
    void PrintQuaternion(const glm::quat& quaternion, std::string name) {
        fprintf(stdout, "%s w: %f, x: %f, y: %f, z: %f\n", name.c_str(), quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    }
    
}

void bounce::MovementComponent::Update() {
    GameEntity* owner = this->owner();
    
    float delta_time = timer_.frame_time();
    float delta_speed = owner->rotation_acceleration() * delta_time;
    
    owner->horizontal_speed(UpdateSpeed(delta_speed, owner->horizontal_acceleration_direction(), owner->horizontal_speed()));
    owner->vertical_speed(UpdateSpeed(delta_speed, owner->vertical_acceleration_direction(), owner->vertical_speed()));
    
    //float yaw = owner->horizontal_angle();
    //float pitch = owner->vertical_angle();
    
    float yaw = owner->horizontal_speed();
    float pitch = owner->vertical_speed();
    
//    if (pitch > PI2) {
//        pitch -= PI2;
//    }
//    else if (pitch < 0.0f) {
//        pitch += PI2;
//    }
//    
//    if (yaw > PI2) {
//        yaw -= PI2;
//    }
//    else if (yaw < 0.0f) {
//        yaw += PI2;
//    }
    
    fprintf(stdout, "yaw: %f, pitch: %f\n", yaw, pitch);
    
    glm::quat orientation = owner->orientation();
    
    glm::vec3 yaw_axis(0.0f, 1.0f, 0.0f);
//    yaw_axis = glm::normalize(glm::rotate(orientation, yaw_axis));
    //yaw_axis = orientation * yaw_axis * -orientation;
//    PrintVector(yaw_axis);
    
    glm::vec3 pitch_axis(1.0f, 0.0f, 0.0f);
//    pitch_axis = glm::rotate(orientation, pitch_axis);
    //pitch_axis = orientation * pitch_axis * -orientation;
//    PrintVector(pitch_axis);
    
    glm::quat pitch_rotation = glm::angleAxis(pitch, pitch_axis);
    PrintQuaternion(pitch_rotation, "pitch");
    glm::quat yaw_rotation = glm::angleAxis(yaw, yaw_axis);
    PrintQuaternion(yaw_rotation, "yaw");

    glm::quat rot = orientation * pitch_rotation * yaw_rotation;
    
//    glm::quat rot = glm::normalize(orientation * pitch_rotation * yaw_rotation);
    
    PrintQuaternion(rot, "rot");
    
    owner->orientation(rot);
}