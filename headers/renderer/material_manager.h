#ifndef BOUNCE_RENDERER_MATERIAL_MANAGER_
#define BOUNCE_RENDERER_MATERIAL_MANAGER_

#include "material.h"

namespace bounce {

    class MaterialManager {
    private:
        std::vector<Material> materials_;
        
    public:
        Material& CreateMaterial();
        
        const Material& GetMaterial(unsigned int index) const;
        
        unsigned int size() const;
        unsigned int next_index() const;
    };
    
    inline Material& MaterialManager::CreateMaterial()
    {
        materials_.push_back(Material());
        return *materials_.rbegin();
    }
    
    inline unsigned int MaterialManager::size() const
    {
        return materials_.size();
    }
    
    inline unsigned int MaterialManager::next_index() const
    {
        return materials_.size();
    }
    
    inline const Material& MaterialManager::GetMaterial(unsigned int index) const
    {
        return materials_[index];
    }

}

#endif // BOUNCE_RENDERER_MATERIAL_MANAGER_
