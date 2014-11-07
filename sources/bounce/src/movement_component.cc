#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "logging/log.h"

#include "movement_component.h"

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

//namespace {
//    glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
//        start = glm::normalize(start);
//        dest = glm::normalize(dest);
//        
//        float cosTheta = glm::dot(start, dest);
//        glm::vec3 rotationAxis;
//        
////        if (cosTheta < -1 + 0.001f){
////            // special case when vectors in opposite directions:
////            // there is no "ideal" rotation axis
////            // So guess one; any will do as long as it's perpendicular to start
////            rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
////            if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
////                rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
////            
////            rotationAxis = glm::normalize(rotationAxis);
////            return glm::angleAxis(bounce::PI, rotationAxis);
////        }
//        
//        rotationAxis = glm::cross(start, dest);
//        
//        float s = sqrt( (1+cosTheta)*2 );
//        float invs = 1 / s;
//        
//        return glm::quat(
//                    s * 0.5f,
//                    rotationAxis.x * invs,
//                    rotationAxis.y * invs,
//                    rotationAxis.z * invs
//                    );
//        
//    }
//    
//    void PrintVector(const glm::vec3& vector) {
//        LOG_DEBUG << "vector x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z << "\n";
//    }
//    
//    void PrintQuaternion(const glm::quat& quaternion, std::wstring name) {
//        LOG_DEBUG << "quaternion name: " << name << ", w: " << quaternion.w << ", x: "
//            << quaternion.x << ", y: " << quaternion.y << ", z: " << quaternion.z;
//    }
//}

void bounce::MovementComponent::Update() {
    GameEntity* owner = this->owner();
    
    float delta_time = timer_.frame_time();
    float delta_speed = owner->rotation_acceleration() * delta_time;
    
    owner->yaw_speed(UpdateSpeed(delta_speed, owner->yaw_acceleration_direction(), owner->yaw_speed()));
    owner->pitch_speed(UpdateSpeed(delta_speed, owner->pitch_acceleration_direction(), owner->pitch_speed()));
    owner->roll_speed(UpdateSpeed(delta_speed, owner->roll_acceleration_direction(), owner->roll_speed()));
    
    float yaw = owner->yaw_speed();
    float pitch = owner->pitch_speed();
    float roll = owner->roll_speed();
    
    LOG_DEBUG << "yaw: " << yaw << ", pitch: " << pitch << ", roll: " << roll << "\n";
    
    glm::quat orientation = owner->orientation();
    
    glm::vec3 yaw_axis(0.0f, 1.0f, 0.0f);
    glm::vec3 pitch_axis(1.0f, 0.0f, 0.0f);
    glm::vec3 roll_axis(0.0f, 0.0f, 1.0f);
    
    glm::quat pitch_rotation = glm::angleAxis(pitch, pitch_axis);
//    PrintQuaternion(pitch_rotation, "pitch");
    glm::quat yaw_rotation = glm::angleAxis(yaw, yaw_axis);
//    PrintQuaternion(yaw_rotation, "yaw");
    glm::quat roll_rotation = glm::angleAxis(roll, roll_axis);
    
    glm::quat rot = orientation * pitch_rotation * yaw_rotation * roll_rotation;
    
//    glm::quat rot = glm::normalize(orientation * pitch_rotation * yaw_rotation);
    
//    PrintQuaternion(rot, "rot");
    
    owner->orientation(rot);
}