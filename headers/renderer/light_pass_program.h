#ifndef BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_
#define BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "shader_program.h"

namespace bounce {

    class LightPassProgram : public ShaderProgram {
    private:
        
        GLuint WVP_location_;
        GLuint position_texture_unit_location_;
        GLuint normal_texture_unit_location_;
        GLuint color_texture_unit_location_;
        GLuint eye_world_position_location_;
        GLuint material_specular_intensity_location_;
        GLuint material_specular_power_location_;
        GLuint screen_size_location_;

    protected:
        LightPassProgram(const ResourceLoader& resource_loader);
        bool Init();
        
    public:
        
        void SetWVP(const glm::mat4& wvp_matrix);
        void SetPositionTextureUnit(unsigned int texture_unit);
        void SetColorTextureUnit(unsigned int texture_unit);
        void SetNormalTextureUnit(unsigned int texture_unit);
        void SetEyeWorldPos(const glm::vec3& eye_world_position);
        void SetMatSpecularIntensity(float intensity);
        void SetMatSpecularPower(float power);
        void SetScreenSize(unsigned int width, unsigned int height);
        


    };

}

#endif // BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_
