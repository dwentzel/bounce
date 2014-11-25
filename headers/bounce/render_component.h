#ifndef BOUNCE_RENDER_COMPONENT_H_
#define BOUNCE_RENDER_COMPONENT_H_

#include "game_component.h"
#include "renderer/model.h"
//#include "render_system.h"

namespace bounce {
  
    class RenderComponent : public GameComponent
    {
    private:
        const unsigned int model_handle_;
        
        glm::mat4 model_matrix_;
        
    public:
        static RenderComponent Create(unsigned int model_handle);
        
        RenderComponent(unsigned int model_handle);

        unsigned int model_handle() const;
        
        const glm::mat4& model_matrix() const;
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
    };
}

#endif