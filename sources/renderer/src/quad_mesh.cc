#include "quad_mesh.h"

bounce::QuadMesh::QuadMesh()
{
    vertex_data_ = new float[12] {
        -1, -1, 0, 1, -1, 0, -1, 1, 0, 1, 1, 0
    };
    
    index_data_ = new unsigned int[6] {
        0, 1, 3, 2, 0, 3
    };
}

bounce::QuadMesh::~QuadMesh()
{
    delete [] vertex_data_;
    delete [] index_data_;
}

