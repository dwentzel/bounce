#ifndef BOUNCE_RENDERER_MESH_H_
#define BOUNCE_RENDERER_MESH_H_

#include <vector>
#include "bounce_gl.h"

namespace bounce {

    class Mesh {
    private:
        GLuint vao_;
        GLuint vertex_buffer_;
        GLuint index_buffer_;
        
//        unsigned int vertex_count_;
        unsigned int index_count_;
                
    public:
        Mesh(GLuint vao, GLuint vertex_buffer, GLuint index_buffer, unsigned int index_count);
        ~Mesh();
        
        void Render();
        
    };

}

#endif // BOUNCE_RENDERER_MESH_H_
