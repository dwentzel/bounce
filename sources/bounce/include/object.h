#ifndef BOUNCE_OBJECT_H_
#define BOUNCE_OBJECT_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "bounce_gl.h"

namespace bounce {

    class Object {
    public:
        Object();
        ~Object();

        void Animate(float delta_time);

        void AccelerateHorizontal(int direction) { horizontal_acceleration_direction_ = direction; }
        void AccelerateVertical(int direction) { vertical_acceleration_direction_ = direction; }

        GLfloat* vertex_data() { return vertex_data_; }
        int vertex_count() { return vertex_count_; }
        GLfloat* normal_data() { return normal_data_; }
        int normal_count() { return normal_count_; }
        GLfloat* color_data() { return color_data_; }
        int color_count() { return color_count_; }
        GLuint* index_data() { return index_data_; }
        int index_count() { return index_count_; }

        const glm::mat4& model_matrix() { return model_matrix_; }

    private:
        float UpdateSpeed(float delta_speed, int acceleration_direction, float speed);

        void CreateVertexData();
        void CreateNormalData();
        void CreateColorData();
        void CreateIndexData();

        int horizontal_acceleration_direction_;
        int vertical_acceleration_direction_;

        float rotation_acceleration_;
        float max_speed_;

        float horizontal_speed_;
        float vertical_speed_;
        float horizontal_angle_;
        float vertical_angle_;

        int vertex_count_;
        GLfloat* vertex_data_;
        int normal_count_;
        GLfloat* normal_data_;
        int color_count_;
        GLfloat* color_data_;
        int index_count_;
        GLuint* index_data_;

        glm::mat4 model_matrix_;
    };

    inline Object::Object() : horizontal_acceleration_direction_(0), vertical_acceleration_direction_(0), rotation_acceleration_(0.0002f), max_speed_(0.1f),
        horizontal_speed_(0.0f), vertical_speed_(0.0f), horizontal_angle_(0.0f), vertical_angle_(0.0f),
        vertex_count_(0), vertex_data_(0), color_count_(0), color_data_(0) {
        CreateVertexData();
        CreateNormalData();
        CreateColorData();
        CreateIndexData();
    }

    inline Object::~Object() {
        delete[] vertex_data_;
        delete[] color_data_;
        delete[] index_data_;
    }

}


#endif // BOUNCE_OBJECT_H_