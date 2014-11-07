#ifndef BOUNCE_SHADERMANAGER_H_
#define BOUNCE_SHADERMANAGER_H_

#include <string>

namespace bounce {
    
    class ShaderManager {
    public:
        GLuint LoadShaders(const std::string& vertex_shader_file_path,
                           const std::string& fragment_shader_file_path);
        
    private:
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_file_path);
    };
    
}

#endif // BOUNCE_SHADERMANAGER_H_
