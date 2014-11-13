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
    
    struct DirectionalLight {
        float* position;
//        float* direction;
        float* color;
        float ambient_intensity;
        float diffuse_intensity;
    };
    
    class ShaderProgram {
    private:
        GLint program_id_;
        GLint vertex_shader_id_;
        GLint fragment_shader_id_;

        GLint mwvp_matrix_id_;
        GLint wvp_matrix_id_;
        GLint view_matrix_id_;
        GLint world_matrix_id_;
        GLint model_matrix_id_;

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

        ShaderProgram();
        
    public:
//        ShaderProgram(GLuint program_id);
        
        void Init();

        void LoadVertexShader(const std::string& shader_code_file_path);
        void LoadFragmentShader(const std::string& shader_code_file_path);
        void LinkProgram();
        
        void UseProgram();

        void LoadUniforms();
        
        void SetLightCount(unsigned int light_count);
        
        void SetLight(unsigned int index, const struct DirectionalLight& light);
        
        void SetMaterial(const Material& material);
        
        void SetModelMatrix(const float* model_matrix);
        void SetWorldMatrix(const float* world_matrix);
        void SetViewMatrix(const float* view_matrix);
        void SetWVPMatrix(const float* wvp_matrix);
        void SetMWVPMatrix(const float* mwvp_matrix);
    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
