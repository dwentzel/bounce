#ifndef BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_
#define BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_

#include "light_pass_program.h"
#include "lights.h"

namespace bounce {
    
    class PointLightPassProgram : public LightPassProgram {
    private:
        struct {
            GLuint color;
            GLuint ambient_intensity;
            GLuint diffuse_intensity;
            GLuint position;
            struct {
                GLuint constant;
                GLuint linear;
                GLuint exp;
            } attenuation;
        } point_light_location_;
        
    public:
        PointLightPassProgram(const ResourceLoader& resource_loader);
        
        void Init();
        
        void SetPointLight(const PointLight& light);
        
    };
    
}

#endif // BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_
