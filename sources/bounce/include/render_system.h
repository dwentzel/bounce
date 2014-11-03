#ifndef BOUNCE_RENDER_SYSTEM_H_
#define BOUNCE_RENDER_SYSTEM_H_

#include "bounce_gl.h"
#include "game_system.h"
#include "application_context.h"
#include "renderer/material_manager.h"
#include "renderer/model_manager.h"
#include "renderer/vertex_buffer.h"
#include "world_manager.h"
#include "renderer/model.h"

namespace bounce {
    
    class RenderSystem : public GameSystem {
    private:
        GLuint program_id_;
        GLuint mvp_matrix_id_;
        GLuint view_matrix_id_;
        GLuint model_matrix_id_;
        GLuint light_id_;
        
        GLuint buffers_[3];
        
        const ApplicationContext& application_context_;
        const WorldManager& world_manager_;
        const ModelManager& model_manager_;
        const MaterialManager& material_manager_;
        const VertexBuffer& vertex_buffer_;
        
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

    public:
        RenderSystem(
                     const ApplicationContext& application_context,
                     const WorldManager& world_manager,
                     const ModelManager& model_manager,
                     const MaterialManager& material_manager,
                     const VertexBuffer& vertex_buffer)
        : application_context_(application_context), world_manager_(world_manager),
          model_manager_(model_manager),
          material_manager_(material_manager), vertex_buffer_(vertex_buffer)
        {
            
        }
        
        virtual void startup();
        virtual void shutdown();
        virtual void update();

        void RenderModel(unsigned int model_handle);
    };
    
}

#endif