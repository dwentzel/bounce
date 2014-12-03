#ifndef BOUNCE_RENDERER_MATERIAL_MANAGER_H_
#define BOUNCE_RENDERER_MATERIAL_MANAGER_H_

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
    
}

#endif // BOUNCE_RENDERER_MATERIAL_MANAGER_H_
