#ifndef BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_
#define BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_

#include "light_pass_program.h"

namespace bounce {

    class DirectionalLightPassProgram : public LightPassProgram {
    private:
        struct {
            GLuint color;
            GLuint ambient_intensity;
            GLuint diffuse_intensity;
            GLuint direction;
        } directional_light_location_;
        
    public:
        void Init();
        
        void SetDirectionalLight(const DirectionalLight& light);
    };

}

#endif // BOUNCE_RENDERER_DIRECTIONAL_LIGHT_PASS_PROGRAM_
