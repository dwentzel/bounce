#ifndef BOUNCE_RENDER_SYSTEM_H_
#define BOUNCE_RENDER_SYSTEM_H_

#include <vector>

#include "framework/object_cache.h"

#include "renderer/opengl_renderer.h"

#include "game_system.h"
#include "application_context.h"

#include "render_component.h"
#include "point_light_component.h"

namespace bounce {
    
    typedef ObjectCache<RenderComponent> RenderComponentCache;
    typedef ObjectCache<PointLightComponent> PointLightComponentCache;
    
    class RenderSystem : public GameSystem {
    private:
        const ApplicationContext& application_context_;
        
        const RenderComponentCache& render_component_cache_;
        const PointLightComponentCache& point_light_component_cache_;
        
        OpenGLRenderer& renderer_;
        
        std::vector<unsigned int> model_handles_;
        
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

    public:
        RenderSystem(const ApplicationContext& application_context,
                     const RenderComponentCache& render_component_cache,
                     const PointLightComponentCache& point_light_component_cache,
                     OpenGLRenderer& renderer);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);

        void AddModel(unsigned int model_handle);
        void RemoveModel(unsigned int model_handle);
        void RenderModel(unsigned int model_handle);
    };
    
}

#endif