#ifndef BOUNCE_RENDERER_LIGHTS_H_
#define BOUNCE_RENDERER_LIGHTS_H_

#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "contrib/enable_clang_warnings.h"

namespace bounce {
    
    struct BaseLight
    {
        glm::vec3 color;
        float ambient_intensity;
        float diffuse_intensity;
        
        BaseLight()
        : color(0.0f), ambient_intensity(0.0f), diffuse_intensity(0.0f)
        {

        }
    };
    
    struct DirectionalLight : public BaseLight
    {
        glm::vec3 direction;
        
        DirectionalLight()
        : direction(0.0f)
        {

        }
    };
    
    struct PointLight : public BaseLight
    {
        glm::vec3 position;
        
        struct
        {
            float constant;
            float linear;
            float exp;
        } attenuation;
        
        PointLight()
        : position(0.0f)
        {
            attenuation.constant = 0.0f;
            attenuation.linear = 0.0f;
            attenuation.exp = 0.0f;
        }
    };
    
    struct SpotLight : public PointLight
    {
        glm::vec3 direction;
        float cutoff;
        
        SpotLight()
        : direction(0.0f), cutoff(0.0f)
        {

        }
    };
    
}
#endif // BOUNCE_RENDERER_LIGHTS_H_
