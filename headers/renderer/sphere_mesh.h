#ifndef BOUNCE_RENDERER_SPHERE_MESH_
#define BOUNCE_RENDERER_SPHERE_MESH_

#include <string>
#include <vector>

#include "bounce_gl.h"
#include "vertex_buffer.h"

namespace bounce {

    class SphereMesh {
    private:
        GLuint vao_;
        GLuint vertex_buffer_;
        GLuint index_buffer_;
        
        unsigned int vertex_count_;
        unsigned int index_count_;
        
        std::vector<float> vertices_;
        std::vector<unsigned int> indices_;
        
    public:
        SphereMesh();
        ~SphereMesh();
        
        void Render();
        
        void ImportFile(const std::string& filename);
    };

}

#endif // BOUNCE_RENDERER_SPHERE_MESH_
