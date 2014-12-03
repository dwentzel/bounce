#ifndef BOUNCE_RENDERER_MODEL_H_
#define BOUNCE_RENDERER_MODEL_H_

#include <vector>

namespace bounce {
    
    class Model {
    private:
        struct MeshData {
            unsigned short index_offset;
            unsigned short index_count;
            unsigned int base_vertex;
            unsigned short material_index;
        };
        
        std::vector<MeshData> meshes_;
        
    public:
        
        void AddMesh(unsigned short index_offset, unsigned short index_count, unsigned short base_vertex, unsigned short material_index);
        
        unsigned short mesh_count() const;
        
        unsigned short GetMeshIndexOffset(unsigned short mesh_index) const;
        unsigned short GetMeshIndexCount(unsigned short mesh_index) const;
        unsigned int GetMeshBaseVertex(unsigned short mesh_index) const;
        unsigned short GetMeshMaterialIndex(unsigned short mesh_index) const;

    };
        
}

#endif // BOUNCE_RENDERER_MODEL_H_