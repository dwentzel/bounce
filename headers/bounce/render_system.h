#ifndef BOUNCE_RENDER_SYSTEM_H_
#define BOUNCE_RENDER_SYSTEM_H_

#include <vector>

#include "renderer/opengl_renderer.h"

#include "game_system.h"
#include "application_context.h"
#include "world_manager.h"

namespace bounce {
    
    class RenderSystem : public GameSystem {
    private:
        const ApplicationContext& application_context_;
        const WorldManager& world_manager_;
        
        OpenGLRenderer& renderer_;
        
        std::vector<unsigned int> model_handles_;
        
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

    public:
        RenderSystem(const ApplicationContext& application_context,
                     const WorldManager& world_manager,
                     OpenGLRenderer& renderer)
        : application_context_(application_context), world_manager_(world_manager), renderer_(renderer)
        {
            
        }
        
        virtual void startup();
        virtual void shutdown();
        virtual void update();

        void AddModel(unsigned int model_handle);
        void RemoveModel(unsigned int model_handle);
        void RenderModel(unsigned int model_handle);
    };
    
}

#endif