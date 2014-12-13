#ifndef BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_H_
#define BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_H_


#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "contrib/enable_clang_warnings.h"

#include "shader_program.h"

namespace bounce {

    class LightPassProgram : public ShaderProgram {
    private:
        GLint VP_location_;
        GLint position_texture_unit_location_;
        GLint normal_texture_unit_location_;
        GLint color_texture_unit_location_;
        GLint eye_world_position_location_;
        GLint material_specular_intensity_location_;
        GLint material_specular_power_location_;
        GLint screen_size_location_;

        LightPassProgram& operator=(const LightPassProgram&) = delete;
    protected:
        LightPassProgram(const ResourceLoader& resource_loader);
        void Init();
        
    public:
        void SetVP(const glm::mat4& vp_matrix);
        void SetPositionTextureUnit(int texture_unit);
        void SetColorTextureUnit(int texture_unit);
        void SetNormalTextureUnit(int texture_unit);
        void SetEyeWorldPos(const glm::vec3& eye_world_position);
        void SetMatSpecularIntensity(float intensity);
        void SetMatSpecularPower(float power);
        void SetScreenSize(unsigned int width, unsigned int height);
        
    };

}

#endif // BOUNCE_RENDERER_LIGHT_PASS_PROGRAM_H_
