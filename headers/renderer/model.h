#ifndef BOUNCE_RENDERER_MODEL_H_
#define BOUNCE_RENDERER_MODEL_H_

#include <vector>

namespace bounce {
    
    class Model {
    private:
        std::vector<int> mesh_start_indices_;
        std::vector<int> mesh_sizes_;
        std::vector<int> material_indices_;
        
    public:
        
        void AddMeshStartIndex(int index);
        void AddMeshMaterialIndex(int index);
        void AddMeshSize(int size);
        
        const std::vector<int>& mesh_start_indices() const;
        const std::vector<int>& mesh_sizes() const;
        const std::vector<int>& material_indices() const;
    };

    inline const std::vector<int>& Model::mesh_start_indices() const
    {
        return mesh_start_indices_;
    }
    
    inline const std::vector<int>& Model::mesh_sizes() const
    {
        return mesh_sizes_;
    }
    
    inline const std::vector<int>& Model::material_indices() const
    {
        return material_indices_;
    }

    
}

#endif // BOUNCE_RENDERER_MODEL_H_