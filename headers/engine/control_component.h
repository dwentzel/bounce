#ifndef BOUNCE_ENGINE_CONTROL_COMPONENT_H_
#define BOUNCE_ENGINE_CONTROL_COMPONENT_H_

#include "game_component.h"
#include "keyboard_state.h"

namespace bounce {
    
    class ControlComponent : public GameComponent {
    private:
        const KeyboardState& keyboard_state_;
        
        ControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state);
        
        ControlComponent& operator=(const ControlComponent&) = delete;
        
    public:
        static ControlComponent Create(GameEntityHandle owner, const KeyboardState& keyboard_state);
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
    
    
}

#endif // BOUNCE_ENGINE_CONTROL_COMPONENT_H_
