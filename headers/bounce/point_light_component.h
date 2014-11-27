#ifndef BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
#define BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_

#include "renderer/lights.h"
#include "game_component.h"

namespace bounce {

    class PointLightComponent : public GameComponent {
    private:
        PointLight light_;
        glm::mat4 model_matrix_;
        
    public:
        static PointLightComponent Create();
        
        PointLightComponent();
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
        
        const glm::vec3& color() const;
        void color(const glm::vec3& color);
        
        float ambient_intensity() const;
        void ambient_intensity(float ambient_intensity);
        
        float diffuse_intensity() const;
        void diffuse_intensity(float diffuse_intensity);
        
        float constant_attenuation() const;
        void constant_attenuation(float constant_attenuation);
        
        float linear_attenuation() const;
        void linear_attenuation(float linear_attenuation);
        
        float exp_attenuation() const;
        void exp_attenuation(float exp_attenuation);
        
        const PointLight& light() const;
        
        const glm::mat4& model_matrix() const;
    };

    inline const glm::vec3& PointLightComponent::color() const
    {
        return light_.color;
    }
    
    inline void PointLightComponent::color(const glm::vec3& color)
    {
        light_.color = color;
    }
    
    inline float PointLightComponent::ambient_intensity() const
    {
        return light_.ambient_intensity;
    }
    
    inline void PointLightComponent::ambient_intensity(float ambient_intensity)
    {
        light_.ambient_intensity = ambient_intensity;
    }
    
    inline float PointLightComponent::diffuse_intensity() const
    {
        return light_.diffuse_intensity;
    }
    
    inline void PointLightComponent::diffuse_intensity(float diffuse_intensity)
    {
        light_.diffuse_intensity = diffuse_intensity;
    }
    
    inline float PointLightComponent::constant_attenuation() const
    {
        return light_.attenuation.constant;
    }
    
    inline void PointLightComponent::constant_attenuation(float constant_attenuation)
    {
        light_.attenuation.constant = constant_attenuation;
    }
    
    inline float PointLightComponent::linear_attenuation() const
    {
        return light_.attenuation.linear;
    }
    
    inline void PointLightComponent::linear_attenuation(float linear_attenuation)
    {
        light_.attenuation.linear = linear_attenuation;
    }
    
    inline float PointLightComponent::exp_attenuation() const
    {
        return light_.attenuation.exp;
    }
    
    inline void PointLightComponent::exp_attenuation(float exp_attenuation)
    {
        light_.attenuation.exp = exp_attenuation;
    }
    
    inline const PointLight& PointLightComponent::light() const
    {
        return light_;
    }
    
    inline const glm::mat4& PointLightComponent::model_matrix() const
    {
        return model_matrix_;
    }
}

#endif // BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
