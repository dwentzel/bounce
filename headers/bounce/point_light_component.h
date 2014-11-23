#ifndef BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
#define BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_

#include "renderer/light_manager.h"
#include "game_component.h"

namespace bounce {

    class PointLightComponent : public GameComponent {
    private:
        LightManager& light_manager_;
        
        unsigned int handle_;
        
        glm::vec3 color_;
        float ambient_intensity_;
        float diffuse_intensity_;
        
        float constant_attenuation_;
        float linear_attenuation_;
        float exp_attenuation_;

    public:
        PointLightComponent(LightManager& light_manager,
                            float ambient_intensity,
                            float diffuse_intensity,
                            float constant_attenuation,
                            float linear_attenuation,
                            float exp_attenuation,
                            glm::vec3 color);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
    };

}

#endif // BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
