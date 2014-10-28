#ifndef BOUNCE_RENDER_COMPONENT_H_
#define BOUNCE_RENDER_COMPONENT_H_

#include "game_component.h"
#include "model.h"
#include "render_system.h"

namespace bounce {
    
    class RenderComponent : public GameComponent
    {
    private:
        RenderSystem* render_system_;
        const Model* model_;
        
    public:
//        RenderComponent(RenderSystem* render_system, Mesh* mesh)
//        : GameComponent(RENDER_COMPONENT), render_system_(render_system), mesh_(mesh) {}

        RenderComponent(RenderSystem* render_system, Model* model)
        : GameComponent(RENDER_COMPONENT), render_system_(render_system), model_(model) {}

        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
}

#endif