#ifndef BOUNCE_MESH_H
#define BOUNCE_MESH_H

#include "bounce_gl.h"

namespace bounce {
    
    class Mesh {
    private:
        int vertex_count_;
        GLfloat* vertex_data_;
        int normal_count_;
        GLfloat* normal_data_;
        int color_count_;
        GLfloat* color_data_;
        int index_count_;
        GLuint* index_data_;
        
        void CreateVertexData();
        void CreateNormalData();
        void CreateColorData();
        void CreateIndexData();
        
    public:
        Mesh();
        ~Mesh();
        
        const GLfloat* vertex_data() const { return vertex_data_; }
        int vertex_count() const { return vertex_count_; }
        const GLfloat* normal_data() const { return normal_data_; }
        int normal_count() const { return normal_count_; }
        const GLfloat* color_data() const { return color_data_; }
        int color_count() const { return color_count_; }
        const GLuint* index_data() const { return index_data_; }
        int index_count() const { return index_count_; }
        
    };
}

#endif