#ifndef BOUNCE_CONTROL_COMPONENT_H_
#define BOUNCE_CONTROL_COMPONENT_H_

#include "game_component.h"
#include "keyboard_state.h"
#include "timer.h"

namespace bounce {
    
    class ControlComponent : public GameComponent {
    private:
        const KeyboardState& keyboard_state_;
        
        const Timer& timer_;
        
    public:
        ControlComponent(const KeyboardState& keyboard_state, const Timer& timer);
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
    
    inline ControlComponent::ControlComponent(const KeyboardState& keyboard_state, const Timer& timer) : GameComponent(CONTROL_COMPONENT),
        keyboard_state_(keyboard_state), timer_(timer) {
        
    }
    
}

#endif // BOUNCE_CONTROL_COMPONENT_H_