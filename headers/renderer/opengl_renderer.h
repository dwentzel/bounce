#ifndef BOUNCE_RENDERER_OPENGL_RENDERER_H_
#define BOUNCE_RENDERER_OPENGL_RENDERER_H_

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

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
#include "model_loader.h"

namespace bounce
{

    class OpenGLRenderer {
    private:
        std::unique_ptr<GBuffer> g_buffer_;
        
        GLuint model_vertex_array_;
        GLuint model_vertex_buffer_;
        GLuint model_element_buffer_;
        
        Mesh* sphere_;
        Mesh* quad_;
        
        GeometryPassProgram geometry_pass_program_;
        DirectionalLightPassProgram directional_light_pass_program_;
        PointLightPassProgram point_light_pass_program_;
        MeshLoader mesh_loader_;
        
        const ModelManager& model_manager_;
        TextureManager& texture_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
        void RunLightPass();
        
        glm::mat4 vp_matrix_;
        
    public:
        OpenGLRenderer(const ResourceLoader& resource_loader,
                       const ModelManager& model_manager,
                       TextureManager& texture_manager,
                       const MaterialManager& material_manager,
                       const VertexBuffer& vertex_buffer);

        virtual ~OpenGLRenderer();
        
        virtual void Startup();
        virtual void Shutdown();

        virtual void SetViewMatrix(const glm::mat4& view_matrix);
        virtual void SetWorldMatrix(const glm::mat4& world_matrix);
        void SetVPMatrix(const glm::mat4& vp_matrix);
        virtual void SetWVPMatrix(const glm::mat4& wvp_matrix);
        
        void Resize(unsigned int width, unsigned int height);
        
        void BeginGeometryPass();
        void EndGeometryPass();
        void BeginLightPasses();
        void BeginPointLightsPass();
        void EndPointLighsPass();
        void RunDirectionalLightPass();
        
        void BufferModelData(const ModelLoader& model_loader);
        
        void RenderModel(unsigned int model_handle);
        void RenderPointLight(const PointLight& point_light);
    };
    
    inline void OpenGLRenderer::SetViewMatrix(const glm::mat4& view_matrix)
    {
        geometry_pass_program_.SetViewMatrix(view_matrix);
    }

    inline void OpenGLRenderer::SetWorldMatrix(const glm::mat4& world_matrix)
    {
        geometry_pass_program_.SetWorldMatrix(world_matrix);
    }

    inline void OpenGLRenderer::SetVPMatrix(const glm::mat4& wvp_matrix)
    {
        vp_matrix_ = wvp_matrix;
        geometry_pass_program_.SetVPMatrix(wvp_matrix);
    }
    
    inline void OpenGLRenderer::SetWVPMatrix(const glm::mat4& wvp_matrix)
    {
        geometry_pass_program_.SetWVPMatrix(wvp_matrix);
    }

}

#endif // BOUNCE_RENDERER_OPENGL_RENDERER_H_
