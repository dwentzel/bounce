#ifndef BOUNCE_RENDERER_QUAD_MESH_
#define BOUNCE_RENDERER_QUAD_MESH_

namespace bounce {

    class QuadMesh {
    private:
        float* vertex_data_;
        unsigned int* index_data_;
        
    public:
        QuadMesh();
        ~QuadMesh();
        
        void Render();
    };

}

#endif // BOUNCE_RENDERER_QUAD_MESH_
