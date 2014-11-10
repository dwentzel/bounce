#ifndef BOUNCE_RENDERER_OPENGL_RENDERER_H_
#define BOUNCE_RENDERER_OPENGL_RENDERER_H_

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "framework/renderer.h"
#include "bounce_gl.h"
#include "model_manager.h"
#include "texture_manager.h"
#include "material_manager.h"
#include "vertex_buffer.h"
#include "shader_manager.h"

namespace bounce
{
    
    class OpenGLRenderer : public Renderer {
    private:
//        GLuint program_id_;
//        GLuint mvp_matrix_id_;
//        GLuint view_matrix_id_;
//        GLuint model_matrix_id_;
//        GLuint light_id_;

        std::shared_ptr<ShaderProgram> current_program_;
        
        GLuint buffers_[1];

        std::string vertex_shader_file_path_;
        std::string fragment_shader_file_path_;
        
        ShaderManager shader_manager_;
        
        const ModelManager& model_manager_;
        const TextureManager& texture_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
    public:
        OpenGLRenderer(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path,
                       const ModelManager& model_manager,
                       const TextureManager& texture_manager,
                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer);
        
        virtual void Startup();
        virtual void Shutdown();
        
        virtual void SetViewMatrix(const float* view_matrix);
        virtual void SetModelMatrix(const float* model_matrix);
        virtual void SetMVPMatrix(const float* mvp_matrix);
        virtual void SetupNewFrame();

//        void LoadVertexShader(const std::string& shader_code_file_path);
//        void LoadFragmentShader(const std::string& shader_code_file_path);
//
//        void LinkProgram();
        
        
        void RenderModel(unsigned int model_handle);
    };
    
    inline void OpenGLRenderer::SetViewMatrix(const float* view_matrix)
    {
        current_program_->SetViewMatrix(view_matrix);
    }
    
    inline void OpenGLRenderer::SetModelMatrix(const float* model_matrix)
    {
        current_program_->SetModelMatrix(model_matrix);
    }
    
    inline void OpenGLRenderer::SetMVPMatrix(const float* mvp_matrix)
    {
        current_program_->SetMVPMatrix(mvp_matrix);
    }

    
}

#endif // BOUNCE_RENDERER_OPENGL_RENDERER_H_