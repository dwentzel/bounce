#ifndef BOUNCE_IMPORTER_IMPORTED_MODEL_H_
#define BOUNCE_IMPORTER_IMPORTED_MODEL_H_

#include <memory>
#include <vector>
#include "imported_material.h"

namespace bounce {

    class ImportedModelImpl;
    
    class ImportedModel {
    private:
        std::unique_ptr<ImportedModelImpl> impl_;
        
        ImportedModel(const ImportedModel&) = delete;
        ImportedModel& operator=(const ImportedModel&) = delete;
        
    public:
        ImportedModel();
        ImportedModel(ImportedModel&& source);
        
        ~ImportedModel();
        
        void AddMesh(unsigned short first_vertex,
                     unsigned short vertex_count,
                     unsigned short first_index,
                     unsigned short index_count,
                     unsigned short material_index);
        
        void AddVertex(float x, float y, float z);
        void AddUV(float x, float y);
        void AddNormal(float x, float y, float z);
        void AddIndex(unsigned short index);
        void AddMaterial(const ImportedMaterial& material);
        
        unsigned short mesh_count() const;
        
        unsigned short GetMeshIndexOffset(unsigned short mesh_index) const;
        unsigned short GetMeshIndexCount(unsigned short mesh_index) const;
        unsigned short GetMeshFirstVertex(unsigned short mesh_index) const;
        unsigned short GetMeshVertexCount(unsigned short mesh_index) const;
        
        const ImportedMaterial& GetMeshMaterial(unsigned short mesh_index) const;
        
        const std::vector<float>& vertex_data() const;
        const std::vector<unsigned short>& index_data() const;
    };

}

#endif // BOUNCE_IMPORTER_IMPORTED_MODEL_H_
