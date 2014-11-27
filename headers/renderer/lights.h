#ifndef BOUNCE_RENDERER_LIGHTS_H_
#define BOUNCE_RENDERER_LIGHTS_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace bounce {
    
    struct BaseLight
    {
        glm::vec3 color;
        float ambient_intensity;
        float diffuse_intensity;
        
        BaseLight()
        {
            color = glm::vec3(0.0f, 0.0f, 0.0f);
            ambient_intensity = 0.0f;
            diffuse_intensity = 0.0f;
        }
    };
    
    struct DirectionalLight : public BaseLight
    {
        glm::vec3 direction;
        
        DirectionalLight()
        {
            direction = glm::vec3(0.0f, 0.0f, 0.0f);
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
        {
            position = glm::vec3(0.0f, 0.0f, 0.0f);
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
        {
            direction = glm::vec3(0.0f, 0.0f, 0.0f);
            cutoff = 0.0f;
        }
    };
    
}
#endif // BOUNCE_RENDERER_LIGHTS_H_