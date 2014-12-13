#ifndef BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_
#define BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_

#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "contrib/enable_clang_warnings.h"

#include "shader_program.h"

namespace bounce {

    class GeometryPassProgram : public ShaderProgram {
    private:
        GLint vp_matrix_location_;
        GLint wvp_matrix_location_;
        GLint view_matrix_location_;
        GLint world_matrix_location_;

        GLint color_texture_unit_location_;

        GeometryPassProgram& operator=(const GeometryPassProgram&) = delete;
        
    public:
        GeometryPassProgram(const ResourceLoader& resource_loader);
        
        void Init();
        
        void SetWorldMatrix(const glm::mat4& world_matrix);
        void SetViewMatrix(const glm::mat4& view_matrix);
        void SetVPMatrix(const glm::mat4& vp_matrix);
        void SetWVPMatrix(const glm::mat4& wvp_matrix);
        void SetColorTextureUnit(int texture_unit);
        
    };

}

#endif // BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_
