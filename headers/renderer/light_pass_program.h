#ifndef BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_
#define BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "shader_program.h"

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
    

    class LightPassProgram : public ShaderProgram {
    private:
        GLuint WVP_location_;
        GLuint position_texture_unit_location_;
        GLuint normal_texture_unit_location_;
        GLuint color_texture_unit_location_;
        GLuint eye_world_position_location_;
        GLuint mat_specular_intensity_location_;
        GLuint mat_specular_power_location_;
        GLuint screen_size_location_;
        
    public:
        void Init();
        
        void SetWVP(const float* WVP);
        void SetPositionTextureUnit(unsigned int texture_unit);
        void SetColorTextureUnit(unsigned int texture_unit);
        void SetNormalTextureUnit(unsigned int texture_unit);
        void SetEyeWorldPos(const float* EyeWorldPos);
        void SetMatSpecularIntensity(float intensity);
        void SetMatSpecularPower(float power);
        void SetScreenSize(unsigned int width, unsigned int height);
        
    };

}

#endif // BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_
