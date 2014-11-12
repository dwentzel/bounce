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
        GLuint program_id_;
        GLuint vertex_shader_id_;
        GLuint fragment_shader_id_;
        
        GLuint light_count_location_;
        
        struct MaterialLocations material_locations_;
        struct DirectionalLightLocation light_location_[10];
        
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
        
//        void SetLightPosition(const float* light_position_data);
        
        void SetLightCount(unsigned int light_count);
        
        void SetLight(unsigned int index, const struct DirectionalLight& light);
        
        void SetMaterial(const Material& material);
        
        void SetViewMatrix(const float* view_matrix);
        void SetModelMatrix(const float* model_matrix);
        void SetMVPMatrix(const float* mvp_matrix);
    };

}

#endif // BOUNCE_RENDERER_SHADER_PROGRAM_
