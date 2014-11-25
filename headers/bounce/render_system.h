#ifndef BOUNCE_RENDER_SYSTEM_H_
#define BOUNCE_RENDER_SYSTEM_H_

#include <vector>

#include "framework/object_cache.h"

#include "renderer/opengl_renderer.h"

#include "render_component.h"

#include "game_system.h"
#include "application_context.h"
#include "world_manager.h"

namespace bounce {
    
    class RenderSystem : public GameSystem {
    private:
        const ApplicationContext& application_context_;
        
        const ObjectCache<RenderComponent>& render_component_cache_;
        
        OpenGLRenderer& renderer_;
        
        std::vector<unsigned int> model_handles_;
        
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

    public:
        RenderSystem(const ApplicationContext& application_context,
                     const ObjectCache<RenderComponent>& render_component_cache,
                     OpenGLRenderer& renderer)
        : application_context_(application_context), render_component_cache_(render_component_cache), renderer_(renderer)
        {
            
        }
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);

        void AddModel(unsigned int model_handle);
        void RemoveModel(unsigned int model_handle);
        void RenderModel(unsigned int model_handle);
    };
    
}

#endif