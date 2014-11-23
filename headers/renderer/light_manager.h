#ifndef BOUNCE_RENDERER_LIGHT_MANAGER_
#define BOUNCE_RENDERER_LIGHT_MANAGER_

#include <functional>
#include <vector>

#include "lights.h"

namespace bounce {

    class LightManager {
    private:
        std::vector<std::reference_wrapper<const PointLight>> point_lights_;
        
    public:
        void AddPointLight(const PointLight& point_light);
        
        const std::vector<std::reference_wrapper<const PointLight>> point_lights() const;
        
    };
}

#endif // BOUNCE_RENDERER_LIGHT_MANAGER_
