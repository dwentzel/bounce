#ifndef BOUNCE_RENDERER_MATERIAL_MANAGER_H_
#define BOUNCE_RENDERER_MATERIAL_MANAGER_H_

#include "framework/object_cache.h"
#include "material.h"

namespace bounce {

    class MaterialManager {
    private:
        ObjectCache<Material> materials_;
        
    public:
        unsigned int GenerateMaterial();
        
        Material& GetMaterial(unsigned int index);
        const Material& GetMaterial(unsigned int index) const;
        
    };
    
}

#endif // BOUNCE_RENDERER_MATERIAL_MANAGER_H_
