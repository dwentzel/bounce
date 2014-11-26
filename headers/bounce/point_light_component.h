#ifndef BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
#define BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_

#include "framework/object_cache.h"
#include "renderer/light_manager.h"
#include "game_component.h"

namespace bounce {

    class PointLightComponent : public GameComponent {
    private:        
        float ambient_intensity_;
        float diffuse_intensity_;
        
        float constant_attenuation_;
        float linear_attenuation_;
        float exp_attenuation_;

        glm::vec3 color_;
        
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
        
    };

    inline const glm::vec3& PointLightComponent::color() const
    {
        return color_;
    }
    
    inline void PointLightComponent::color(const glm::vec3& color)
    {
        color_ = color;
    }
    
    inline float PointLightComponent::ambient_intensity() const
    {
        return ambient_intensity_;
    }
    
    inline void PointLightComponent::ambient_intensity(float ambient_intensity)
    {
        ambient_intensity_ = ambient_intensity;
    }
    
    inline float PointLightComponent::diffuse_intensity() const
    {
        return diffuse_intensity_;
    }
    
    inline void PointLightComponent::diffuse_intensity(float diffuse_intensity)
    {
        diffuse_intensity_ = diffuse_intensity;
    }
    
    inline float PointLightComponent::constant_attenuation() const
    {
        return constant_attenuation_;
    }
    
    inline void PointLightComponent::constant_attenuation(float constant_attenuation)
    {
        constant_attenuation_ = constant_attenuation;
    }
    
    inline float PointLightComponent::linear_attenuation() const
    {
        return linear_attenuation_;
    }
    
    inline void PointLightComponent::linear_attenuation(float linear_attenuation)
    {
        linear_attenuation_ = linear_attenuation;
    }
    
    inline float PointLightComponent::exp_attenuation() const
    {
        return exp_attenuation_;
    }
    
    inline void PointLightComponent::exp_attenuation(float exp_attenuation)
    {
        exp_attenuation_ = exp_attenuation;
    }
    
    typedef ObjectCache<PointLightComponent> PointLightComponentCache;
//    typedef ObjectCacheHandle<PointLightComponent> PointLightComponentHandle;
    
}

#endif // BOUNCE_BOUNCE_POINT_LIGHT_COMPONENT_
