#ifndef BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
#define BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_

#include "renderer/lights.h"
#include "renderer/light_manager.h"
#include "game_component.h"

namespace bounce {

    class PointLightComponent : public GameComponent {
    private:
        LightManager& light_manager_;
        PointLight point_light_;

    public:
        PointLightComponent(LightManager& light_manager, const PointLight& point_light);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
    };

}

#endif // BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
