#ifndef BOUNCE_IMPORTER_IMPORTED_MODEL_H_
#define BOUNCE_IMPORTER_IMPORTED_MODEL_H_

#include <memory>
#include <vector>
#include "imported_material.h"

namespace bounce {

    class ImportedModelImpl;
    
    class ImportedModel {
    private:
        ImportedModelImpl* impl_;
        
        ImportedModel(const ImportedModel&) = delete;
        ImportedModel& operator=(const ImportedModel&) = delete;
        
    public:
        ImportedModel();
        ImportedModel(ImportedModel&& source);
        
        ~ImportedModel();
        
        void AddMesh(
            unsigned int first_vertex,
            unsigned int vertex_count,
            unsigned int first_index,
            unsigned int index_count,
            unsigned int material_index);
        
        void AddVertex(float x, float y, float z);
        void AddUV(float x, float y);
        void AddNormal(float x, float y, float z);
        void AddIndex(unsigned short index);
        void AddMaterial(const ImportedMaterial& material);
        
        unsigned short mesh_count() const;
        
        unsigned int GetMeshIndexOffset(unsigned short mesh_index) const;
        unsigned int GetMeshIndexCount(unsigned short mesh_index) const;
        unsigned int GetMeshFirstVertex(unsigned short mesh_index) const;
        unsigned int GetMeshVertexCount(unsigned short mesh_index) const;
        
        const ImportedMaterial& GetMeshMaterial(unsigned short mesh_index) const;
        
        const std::vector<float>& vertex_data() const;
        const std::vector<unsigned short>& index_data() const;
    };

}

#endif // BOUNCE_IMPORTER_IMPORTED_MODEL_H_
