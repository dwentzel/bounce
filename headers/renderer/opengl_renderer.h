#ifndef BOUNCE_RENDERER_OPENGL_RENDERER_H_
#define BOUNCE_RENDERER_OPENGL_RENDERER_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "framework/renderer.h"
#include "bounce_gl.h"
#include "model_manager.h"
#include "material_manager.h"
#include "vertex_buffer.h"

namespace bounce
{
    
    class OpenGLRenderer : public Renderer {
    private:
        GLuint program_id_;
        GLuint mvp_matrix_id_;
        GLuint view_matrix_id_;
        GLuint model_matrix_id_;
        GLuint light_id_;
        
        GLuint buffers_[3];
        
        glm::mat4 projection_matrix_;
        glm::mat4 view_matrix_;
        glm::mat4 model_matrix_;
        
        const ModelManager& model_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
    public:
        OpenGLRenderer(const ModelManager& model_manager, const MaterialManager& material_manager, const VertexBuffer& vertex_buffer);
        
        virtual void Startup();
        virtual void Shutdown();
        
        virtual void SetViewMatrix(const float* view_matrix);
        virtual void SetModelMatrix(const float* model_matrix);
        virtual void SetMVPMatrix(const float* mvp_matrix);
        virtual void SetupNewFrame();
        
        void Update();
        void RenderModel(unsigned int model_handle);
    };
    
    inline void OpenGLRenderer::SetViewMatrix(const float* view_matrix)
    {
        glUniformMatrix4fv(view_matrix_id_, 1, GL_FALSE, view_matrix);
    }
    
    inline void OpenGLRenderer::SetModelMatrix(const float* model_matrix)
    {
        glUniformMatrix4fv(model_matrix_id_, 1, GL_FALSE, model_matrix);
    }
    
    inline void OpenGLRenderer::SetMVPMatrix(const float* mvp_matrix)
    {
        glUniformMatrix4fv(mvp_matrix_id_, 1, GL_FALSE, mvp_matrix);
    }

    
}

#endif // BOUNCE_RENDERER_OPENGL_RENDERER_H_