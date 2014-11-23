#ifndef BOUNCE_RENDERER_LIGHT_MANAGER_
#define BOUNCE_RENDERER_LIGHT_MANAGER_

#include <vector>

#include "lights.h"

namespace bounce {

    class LightManager {
    private:
        std::vector<PointLight> point_lights_;
        
    public:
        unsigned int GenerateLight();
        //void AddPointLight(const PointLight& point_light);
        
        PointLight& GetLight(unsigned int handle);
        
        const std::vector<PointLight> point_lights() const;
        
    };
}

#endif // BOUNCE_RENDERER_LIGHT_MANAGER_
