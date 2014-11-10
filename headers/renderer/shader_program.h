#ifndef BOUNCE_RENDERER_SHADER_PROGRAM_
#define BOUNCE_RENDERER_SHADER_PROGRAM_

#include "bounce_gl.h"
#include <string>
#include <unordered_map>

namespace bounce {

    class ShaderProgram {
    private:
        GLuint program_id_;
        GLuint vertex_shader_id_;
        GLuint fragment_shader_id_;
        
//        GLuint mvp_matrix_id_;
//        GLuint view_matrix_id_;
//        GLuint model_matrix_id_;
//        GLuint light_id_;
        
        std::unordered_map<std::string, GLint> uniform_location_map_;
        
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_code_file_path);
        
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);

    public:
        ShaderProgram(GLuint program_id);

        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();
        
        void UseProgram();

        void LoadUniformLocation(const std::string& uniform);
        
        void SetUniform(const std::string& uniform, const float* data);
        void SetUniform(const std::string& uniform, float data);
        
        void SetViewMatrix(const float* view_matrix);
        void SetModelMatrix(const float* model_matrix);
        void SetMVPMatrix(const float* mvp_matrix);
    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
