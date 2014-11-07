#ifndef BOUNCE_RENDER_COMPONENT_H_
#define BOUNCE_RENDER_COMPONENT_H_

#include "game_component.h"
#include "renderer/model.h"
#include "render_system.h"

namespace bounce {
    
    class RenderComponent : public GameComponent
    {
    private:
        RenderSystem* render_system_;
        const unsigned int model_handle_;
        
    public:
        RenderComponent(RenderSystem* render_system, unsigned int model_handle)
        : GameComponent(RENDER_COMPONENT), render_system_(render_system), model_handle_(model_handle) {}

        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
}

#endif