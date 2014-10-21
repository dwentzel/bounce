#include <complex>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "object.h"

#include <Windows.h>

void bounce::Object::UpdateSpeed(float delta_speed, int acceleration_direction, float* speed) {
    if (acceleration_direction > 0) {
        if (*speed < max_speed_) {
            *speed += delta_speed;

            if (*speed > max_speed_) {
                *speed = max_speed_;
            }
        }
    }
    else if (acceleration_direction < 0) {
        if (*speed > -max_speed_) {
            *speed -= delta_speed;

            if (*speed < -max_speed_) {
                *speed = -max_speed_;
            }
        }
    }
    else {
        if (*speed > 0) {
            *speed -= delta_speed;
        }
        else if (*speed < 0) {
            *speed += delta_speed;
        }
    }

    if (std::abs(*speed) < delta_speed) {
        if (acceleration_direction == 0) {
            *speed = 0.0f;
        }
    }
}

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
    start = glm::normalize(start);
    dest = glm::normalize(dest);

    float cosTheta = glm::dot(start, dest);
    glm::vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
        if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = glm::normalize(rotationAxis);
        return glm::angleAxis(180.0f, rotationAxis);
    }

    rotationAxis = glm::cross(start, dest);

    float s = sqrt((1 + cosTheta) * 2);
    float invs = 1 / s;

    return glm::quat(
        s * 0.5f,
        rotationAxis.x * invs,
        rotationAxis.y * invs,
        rotationAxis.z * invs
        );

}


void bounce::Object::Animate(float delta_time)
{
    char debug_buffer[1000];
    sprintf(debug_buffer, "delta_time: %f\n", delta_time);
    OutputDebugString(debug_buffer);

    float delta_speed = rotation_acceleration_ * delta_time;

    UpdateSpeed(delta_speed, horizontal_acceleration_direction_, &horizontal_speed_);
    UpdateSpeed(delta_speed, vertical_acceleration_direction_, &vertical_speed_);

    horizontal_angle_ += horizontal_speed_;
    vertical_angle_ += vertical_speed_;

    if (vertical_angle_ > PI2) {
        vertical_angle_ -= PI2;
    }
    else if (vertical_angle_ < 0.0f) {
        vertical_angle_ += PI2;
    }

    if (horizontal_angle_ > PI2) {
        horizontal_angle_ -= PI2;
    }
    else if (horizontal_angle_ < 0.0f) {
        horizontal_angle_ += PI2;
    }

    glm::vec3 direction(
        cos(vertical_angle_) * sin(horizontal_angle_),
        sin(vertical_angle_),
        cos(vertical_angle_) * cos(horizontal_angle_));
    
    //glm::quat horizontal = glm::angleAxis(horizontal_angle_, glm::normalize(glm::vec3(0.0f, cos(vertical_angle_), sin(vertical_angle_))));
    //glm::quat vertical = glm::angleAxis(vertical_angle_, glm::normalize(glm::vec3(cos(horizontal_angle_), 0.0f, sin(horizontal_angle_))));

    //glm::quat rot = vertical * horizontal;

    //model_matrix_ = glm::toMat4(rot);

    //model_matrix_ = glm::rotate(glm::mat4(1.0f), vertical_angle_, glm::vec3(1, 0, 0)) *
    //    glm::rotate(glm::mat4(1.0f), horizontal_angle_, glm::vec3(0, 1, 0))
    //    ;

    glm::quat rot = RotationBetweenVectors(glm::vec3(1, 0, 0), direction);
    model_matrix_ = glm::toMat4(rot);
    //model_matrix_ = glm::rotate(glm::mat4(1.0f), horizontal_angle_, glm::vec3(0, 1, 0));

    //model_matrix_ = glm::rotate(model_matrix_, vertical_angle_, direction);
    
    
        //glm::rotate(glm::mat4(1.0f), horizontal_angle_, glm::vec3(0, 1, 0))
        //;
}

void bounce::Object::CreateIndexData() {
    GLuint* index_data = new GLuint[36] {
        0, 1, 2,
            0, 2, 3,
            3, 2, 6,
            3, 6, 7,
            6, 4, 7,
            6, 5, 4,
            4, 5, 1,
            4, 1, 0,
            5, 6, 2,
            5, 2, 1,
            0, 7, 4,
            0, 3, 7
    };


    index_data_ = index_data;
    index_count_ = 36;
}

void bounce::Object::CreateVertexData() {
    //GLfloat* vertex_data = new GLfloat[32]
    //{
    //    -1.0f, -1.0f, -1.0f,
    //    -1.0f, 1.0f, -1.0f,
    //     1.0f, 1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,
    //    -1.0f, -1.0f, 1.0f,
    //    -1.0f, 1.0f,  1.0f,
    //     1.0f, 1.0f,  1.0f,
    //     1.0f, -1.0f, 1.0f,
    //};

    //vertex_data_ = vertex_data;
    //vertex_count_ = 32;

    GLfloat* vertex_data = new GLfloat[144] {
        -1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 1.0f,

            -1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,

            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 1.0f,

            1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 1.0f,

            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f
    };

    vertex_data_ = vertex_data;
    vertex_count_ = 144;
}

void bounce::Object::CreateNormalData() {
    GLfloat* normal_data = new GLfloat[108];
    int i = 0;

    for (i; i < 6; ++i) {
        normal_data[i * 3] = -1.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }

    for (i; i < 12; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = -1.0f;
    }

    for (i; i < 18; ++i) {
        normal_data[i * 3] = 1.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }

    for (i; i < 24; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 1.0f;
    }

    for (i; i < 30; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = -1.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }

    for (i; i < 36; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 1.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }

    normal_data_ = normal_data;
    normal_count_ = 108;
}

void bounce::Object::CreateColorData()
{
    GLfloat* color_data = new GLfloat[12 * 3 * 3];

    int sides = 6;
    int verticesPerSide = 6;
    int colorsPerVertex = 3;
    int colorsPerSide = verticesPerSide * colorsPerVertex;

    for (int i = 0; i < sides; i++) {
        GLfloat val = 0.5f; //((float) rand() / (RAND_MAX));

        for (int j = 0; j < verticesPerSide; j++) {
            int index = i * colorsPerSide + j * colorsPerVertex;

            if (i == 1) {
                color_data[index] = 1.0f;
                color_data[index + 1] = 1.0f;
            }
            if (i % 2 == 0) {
                color_data[index] = 1.0f;
            }
            if (i % 3 == 0) {
                color_data[index + 1] = 1.0f;
            }
            if (i % 4 == 0 || i % 5 == 0) {
                color_data[index + 2] = 1.0f;
            }

            //			else {
            //				colorDataArray[index] = val;
            //				colorDataArray[index + 1] = val;
            //				colorDataArray[index + 2] = val;
            //			}

            //			std::cout << "i: " << i << " j: " << j << std::endl;
            //			std::cout << index << " ";
            //			std::cout << index + 1 << " ";
            //			std::cout << index + 2 << " ";
            //			std::cout << std::endl << std::endl;

        }
    }

    //	for (int i = 0; i < 108; i++) {
    //		std::cout << colorDataArray[i] << std::endl;
    //	}

    color_data_ = color_data;
    color_count_ = 108;
}