#ifndef BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_H_
#define BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_H_

#include "light_pass_program.h"
#include "lights.h"

namespace bounce {
    
    class PointLightPassProgram : public LightPassProgram {
    private:
        struct {
            GLint color;
            GLint ambient_intensity;
            GLint diffuse_intensity;
            GLint position;
            struct {
                GLint constant;
                GLint linear;
                GLint exp;
            } attenuation;
        } point_light_location_;
        
    public:
        PointLightPassProgram(const ResourceLoader& resource_loader);
        
        void Init();
        
        void SetPointLight(const PointLight& light);
        
    };
    
}

#endif // BOUNCE_RENDERER_POINT_LIGHT_PASS_PROGRAM_H_
