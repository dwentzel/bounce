#ifndef BOUNCE_RENDER_COMPONENT_H_
#define BOUNCE_RENDER_COMPONENT_H_

#include "game_component.h"
#include "mesh.h"
#include "render_system.h"

namespace bounce {
    
    class RenderComponent : public GameComponent
    {
    private:
        RenderSystem* render_system_;
        const Mesh* mesh_;
        
    public:
        RenderComponent(RenderSystem* render_system, Mesh* mesh)
        : GameComponent(RENDER_COMPONENT), render_system_(render_system), mesh_(mesh) {}
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
}

#endif