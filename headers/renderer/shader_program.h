#ifndef BOUNCE_RENDERER_SHADER_PROGRAM_
#define BOUNCE_RENDERER_SHADER_PROGRAM_

#include "bounce_gl.h"
#include <string>

#include "material.h"

namespace bounce {
    
    class ShaderProgram {
    private:
        static std::string base_path_;
        
        GLint program_id_;
        GLint vertex_shader_id_;
        GLint fragment_shader_id_;
        
    protected:
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_code_file_path);
        
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);
        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();

        void CreateProgram();
        
        GLint GetUniformLocation(const GLchar* uniform);
        
        ShaderProgram();
        
    public:
        static void base_path(const std::string& path);
        
        void UseProgram();

        void LoadUniforms();
        
        void SetLightCount(unsigned int light_count);
        
        void SetLight(unsigned int index, const struct DirectionalLight& light);
        
        void SetMaterial(const Material& material);
        

    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
