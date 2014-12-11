#ifndef BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_H_
#define BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_H_

#include "light_pass_program.h"
#include "lights.h"

namespace bounce {

    class DirectionalLightPassProgram : public LightPassProgram {
    private:
        struct {
            GLint color;
            GLint ambient_intensity;
            GLint diffuse_intensity;
            GLint direction;
        } directional_light_location_;
        
    public:
        DirectionalLightPassProgram(const ResourceLoader& resource_loader);
        
        void Init();
        
        void SetDirectionalLight(const DirectionalLight& light);
        
    };

}

#endif // BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_H_
