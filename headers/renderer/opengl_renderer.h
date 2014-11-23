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
#include "geometry_pass_program.h"
#include "directional_light_pass_program.h"
#include "point_light_pass_program.h"
#include "g_buffer.h"
#include "mesh_loader.h"
#include "mesh.h"

namespace bounce
{
    
    class OpenGLRenderer {
    private:
        GBuffer g_buffer_;
        
        GLuint model_vertex_array_;
        GLuint directional_vertex_array_;
        
        GLuint model_vertex_buffer_;
        GLuint directional_vertex_buffer_;
        
        PointLight point_lights_[3];
        
        std::vector<unsigned int> model_handles_;
        
        Mesh* sphere_;
        Mesh* quad_;
        
        GeometryPassProgram geometry_pass_program_;
        DirectionalLightPassProgram directional_light_pass_program_;
        PointLightPassProgram point_light_pass_program_;
        MeshLoader mesh_loader_;
        
        
        const ModelManager& model_manager_;
        const TextureManager& texture_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
        void BeginGeometryPass();
        void EndGeometryPass();
        void BeginLightPasses();
        void RunDirectionalLightPass();
        void RunPointLightsPass();
        void RunLightPass();
        
        glm::mat4 wvp_matrix_;
        
    public:
        OpenGLRenderer(const ResourceLoader& resource_loader,
                       const ModelManager& model_manager,
                       const TextureManager& texture_manager,
                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer);

        ~OpenGLRenderer();
        
        virtual void Startup();
        virtual void Shutdown();

        virtual void SetModelMatrix(const glm::mat4& model_matrix);
        virtual void SetViewMatrix(const glm::mat4& view_matrix);
        virtual void SetWorldMatrix(const glm::mat4& world_matrix);
        virtual void SetWVPMatrix(const glm::mat4& wvp_matrix);
        virtual void SetMWVPMatrix(const glm::mat4& mwvp_matrix);
        
        virtual void ClearModels();
        virtual void AddModel(unsigned int model_handle);
        
        void BeginFrame();
        void EndFrame();
        
        void RenderModel(unsigned int model_handle);
        
    };
    
    inline void OpenGLRenderer::SetModelMatrix(const glm::mat4& model_matrix)
    {
        geometry_pass_program_.SetModelMatrix(model_matrix);
    }
    
    inline void OpenGLRenderer::SetViewMatrix(const glm::mat4& view_matrix)
    {
        geometry_pass_program_.SetViewMatrix(view_matrix);
    }

    inline void OpenGLRenderer::SetWorldMatrix(const glm::mat4& world_matrix)
    {
        geometry_pass_program_.SetWorldMatrix(world_matrix);
    }

    
    inline void OpenGLRenderer::SetWVPMatrix(const glm::mat4& wvp_matrix)
    {
        wvp_matrix_ = wvp_matrix;
        geometry_pass_program_.SetWVPMatrix(wvp_matrix);
    }

    inline void OpenGLRenderer::SetMWVPMatrix(const glm::mat4& mwvp_matrix)
    {
        geometry_pass_program_.SetMWVPMatrix(mwvp_matrix);
    }
    
    
}

#endif // BOUNCE_RENDERER_OPENGL_RENDERER_H_