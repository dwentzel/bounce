#ifndef BOUNCE_ENGINE_RENDER_SYSTEM_H_
#define BOUNCE_ENGINE_RENDER_SYSTEM_H_

#include <vector>

#include "framework/object_cache.h"
#include "renderer/opengl_renderer.h"

#include "application_context.h"
#include "game_entity.h"
#include "game_system.h"

namespace bounce {
    
    typedef ObjectCache<GameEntity> GameEntityCache;
    
    class RenderSystem : public GameSystem {
    public:
        RenderSystem(const ApplicationContext& application_context,
                     const WindowContext& window_context,
                     GameEntityCache& game_entity_cache,
                     GameComponentManager& game_component_manager,
                     OpenGLRenderer& renderer);
        
        virtual ~RenderSystem();
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);

        void RenderModel(unsigned int model_handle);
        
    private:
        const ApplicationContext& application_context_;
        const WindowContext& window_context_;
        
        GameEntityCache& game_entity_cache_;
        GameComponentManager& component_manager_;
        
        OpenGLRenderer& renderer_;
        
        std::vector<unsigned int> model_handles_;

    private:
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;
        
        RenderSystem(RenderSystem&&) = delete;
        RenderSystem& operator=(RenderSystem&&) = delete;

    };
    
}

#endif // BOUNCE_ENGINE_RENDER_SYSTEM_H_
