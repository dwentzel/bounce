#ifndef BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_
#define BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "shader_program.h"

namespace bounce {

    class GeometryPassProgram : public ShaderProgram {
    private:
        GLint mwvp_matrix_location_;
        GLint wvp_matrix_location_;
        GLint view_matrix_location_;
        GLint world_matrix_location_;
        GLint model_matrix_location_;

        GLint color_texture_unit_location_;

        GeometryPassProgram& operator=(const GeometryPassProgram&) = delete;
        
    public:
        GeometryPassProgram(const ResourceLoader& resource_loader);
        
        void Init();
        
        void SetModelMatrix(const glm::mat4& model_matrix);
        void SetWorldMatrix(const glm::mat4& world_matrix);
        void SetViewMatrix(const glm::mat4& view_matrix);
        void SetWVPMatrix(const glm::mat4& wvp_matrix);
        void SetMWVPMatrix(const glm::mat4& mwvp_matrix);
        void SetColorTextureUnit(int texture_unit);
        
    };

}

#endif // BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_H_
