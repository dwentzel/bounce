#ifndef BOUNCE_SHADERMANAGER_H_
#define BOUNCE_SHADERMANAGER_H_

#include <string>
#include "bounce_gl.h"

namespace bounce {
    
    class ShaderManager {
    private:
        GLuint vertex_shader_id_;
        GLuint fragment_shader_id_;
        GLuint program_id_;
        
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_code_file_path);
    
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);
    public:
        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();
        
        void program_id(GLuint id);
        
//        GLuint LoadShaders(const std::string& vertex_shader_file_path,
//                           const std::string& fragment_shader_file_path);
    };
    
}

#endif // BOUNCE_SHADERMANAGER_H_
