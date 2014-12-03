#ifndef BOUNCE_RENDERER_SHADER_PROGRAM_H_
#define BOUNCE_RENDERER_SHADER_PROGRAM_H_


#include <string>
#include "framework/resource_loader.h"
#include "bounce_gl.h"

namespace bounce {

    class ShaderProgram {
    private:
        GLuint program_id_;
        GLuint vertex_shader_id_;
        GLuint fragment_shader_id_;
        
        const ResourceLoader& resource_loader_;
        
    protected:
        void CompileShader(const int& shader_id, const std::string& shader_code);
        
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);
        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();

        void CreateProgram();
        
        GLuint GetUniformLocation(const GLchar* uniform);
        
        ShaderProgram(const ResourceLoader& resource_loader);
        
    public:
        void UseProgram();
        
    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_H_
