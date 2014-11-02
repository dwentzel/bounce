#ifndef BOUNCE_CONTROL_COMPONENT_H_
#define BOUNCE_CONTROL_COMPONENT_H_

#include "game_component.h"
#include "keyboard_state.h"
#include "timer.h"

namespace bounce {
    
    class ControlComponent : public GameComponent {
    private:
        const KeyboardState& keyboard_state_;
        
//        const Timer& timer_;
        
        ControlComponent(const ControlComponent&) = delete;
        ControlComponent& operator=(const ControlComponent&) = delete;

    public:
//        ControlComponent(const KeyboardState& keyboard_state, const Timer& timer);
  
        ControlComponent(const KeyboardState& keyboard_state);
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };

//    inline ControlComponent::ControlComponent(const KeyboardState& keyboard_state, const Timer& timer) : GameComponent(CONTROL_COMPONENT),
//    keyboard_state_(keyboard_state), timer_(timer) {
//        
//    }

    
    inline ControlComponent::ControlComponent(const KeyboardState& keyboard_state) : GameComponent(CONTROL_COMPONENT),
        keyboard_state_(keyboard_state) {
        
    }
    
}

#endif // BOUNCE_CONTROL_COMPONENT_H_