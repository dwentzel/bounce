#ifndef BOUNCE_ENGINE_RENDER_COMPONENT_H_
#define BOUNCE_ENGINE_RENDER_COMPONENT_H_

#include "renderer/model.h"
#include "game_component.h"

namespace bounce {
  
    class RenderComponent : public GameComponent
    {
    private:
        const unsigned int model_handle_;
        glm::mat4 model_matrix_;

        RenderComponent(GameEntityHandle owner, unsigned int model_handle);
        
        RenderComponent(const RenderComponent&) = delete;
        RenderComponent& operator=(const RenderComponent&) = delete;

    public:
        static RenderComponent Create(GameEntityHandle owner, unsigned int model_handle);

        RenderComponent(RenderComponent&& source);

        unsigned int model_handle() const;
        
        const glm::mat4& model_matrix() const;
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
        
    };
    
}

#endif // BOUNCE_ENGINE_RENDER_COMPONENT_H_
