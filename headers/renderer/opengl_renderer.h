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
//#include "shader_manager.h"
#include "geometry_pass_program.h"
#include "directional_light_pass_program.h"
#include "point_light_pass_program.h"
#include "g_buffer.h"

namespace bounce
{

    
    class OpenGLRenderer : public Renderer {
    private:
        ShaderProgram* current_program_;
        GBuffer g_buffer_;
        
        GLuint buffers_[1];
        
        std::string vertex_shader_file_path_;
        std::string fragment_shader_file_path_;
        
        GeometryPassProgram geometry_pass_program_;
        DirectionalLightPassProgram directional_light_pass_program_;
        PointLightPassProgram point_light_pass_program_;
        
        std::vector<unsigned int> model_handles_;
        
        const ModelManager& model_manager_;
        const TextureManager& texture_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
        void RunGeometryPass();
        void BeginLightPasses();
        void RunPointLightsPass();
        void RunDirectionalLightPass();
        
        void RunLightPass();
        void RenderModel(unsigned int model_handle);
        
    public:
        OpenGLRenderer(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path,
                       const ModelManager& model_manager,
                       const TextureManager& texture_manager,
                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer);
        
        virtual void Startup();
        virtual void Shutdown();

        virtual void SetModelMatrix(const float* model_matrix);
        virtual void SetViewMatrix(const float* view_matrix);
        virtual void SetWorldMatrix(const float* world_matrix);
        virtual void SetWVPMatrix(const float* wvp_matrix);
        virtual void SetMWVPMatrix(const float* mwvp_matrix);
        
        virtual void ClearModels();
        virtual void AddModel(unsigned int model_handle);
        
        virtual void RenderFrame();
        
    };
    
    inline void OpenGLRenderer::SetModelMatrix(const float* model_matrix)
    {
//        current_program_->SetModelMatrix(model_matrix);
    }
    
    inline void OpenGLRenderer::SetViewMatrix(const float* view_matrix)
    {
//        current_program_->SetViewMatrix(view_matrix);
    }

    inline void OpenGLRenderer::SetWorldMatrix(const float* world_matrix)
    {
//        current_program_->SetWorldMatrix(world_matrix);
    }

    
    inline void OpenGLRenderer::SetWVPMatrix(const float* wvp_matrix)
    {
//        current_program_->SetWVPMatrix(wvp_matrix);
    }

    inline void OpenGLRenderer::SetMWVPMatrix(const float* mwvp_matrix)
    {
//        current_program_->SetMWVPMatrix(mwvp_matrix);
    }
    
    
}

#endif // BOUNCE_RENDERER_OPENGL_RENDERER_H_