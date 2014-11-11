#ifndef BOUNCE_RENDERER_SHADER_PROGRAM_
#define BOUNCE_RENDERER_SHADER_PROGRAM_

#include "bounce_gl.h"
#include <string>

#include "material.h"

namespace bounce {

    struct MaterialUniforms {
        GLuint diffuse_id;
        GLuint ambient_id;
        GLuint specular_id;
        GLuint emissive_id;
        GLuint shininess_id;
    };
    
    class ShaderProgram {
    private:
        GLuint program_id_;
        GLuint vertex_shader_id_;
        GLuint fragment_shader_id_;
        
        MaterialUniforms material_uniforms_;
        
        GLuint mvp_matrix_id_;
        GLuint view_matrix_id_;
        GLuint model_matrix_id_;
        GLuint light_position_id_;
        
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_code_file_path);
        
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);

    public:
        ShaderProgram(GLuint program_id);

        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();
        
        void UseProgram();

        void LoadUniforms();
        
        void SetLightPosition(const float* light_position_data);
        
        void SetMaterial(const Material& material);
        
        void SetViewMatrix(const float* view_matrix);
        void SetModelMatrix(const float* model_matrix);
        void SetMVPMatrix(const float* mvp_matrix);
    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
