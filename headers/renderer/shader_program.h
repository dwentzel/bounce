#ifndef BOUNCE_RENDERER_SHADER_PROGRAM_
#define BOUNCE_RENDERER_SHADER_PROGRAM_

#include "bounce_gl.h"
#include <string>

#include "material.h"

namespace bounce {

    struct MaterialLocations {
        GLuint diffuse_id;
        GLuint ambient_id;
        GLuint specular_id;
        GLuint emissive_id;
        GLuint shininess_id;
    };
    
    struct DirectionalLightLocation {
        GLuint position;
        GLuint color;
        GLuint ambient_intensity;
        GLuint direction;
        GLuint diffuse_intensity;
    };
        
    class ShaderProgram {
    private:
        static std::string base_path_;
        
        GLint program_id_;
        GLint vertex_shader_id_;
        GLint fragment_shader_id_;
        
//        GLuint light_count_location_;
//        
//        struct MaterialLocations material_locations_;
//        struct DirectionalLightLocation light_location_[10];
//        
//        GLuint light_position_id_;
        
    protected:
        void CompileShader(const int& shader_id, const std::string& shader_code);
        std::string LoadShaderCode(const std::string& shader_code_file_path);
        
        void LoadShader(const std::string& shader_code_file_path, GLuint shader_id);
        
        GLint GetUniformLocation(const std::string& name);
        
        ShaderProgram();
        
        GLint program_id() const;
        
        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();
        
    public:
        static void base_path(const std::string& path);
        
        void Init();
        
        void UseProgram();

        void LoadUniforms();
        
        void SetLightCount(unsigned int light_count);
        
        void SetLight(unsigned int index, const struct DirectionalLight& light);
        
        void SetMaterial(const Material& material);
    };

    inline GLint ShaderProgram::program_id() const
    {
        return program_id_;
    }
}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
