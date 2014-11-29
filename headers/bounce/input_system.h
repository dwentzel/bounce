#ifndef BOUNCE_BOUNCE_INPUT_SYSTEM_
#define BOUNCE_BOUNCE_INPUT_SYSTEM_

#include "keyboard_state.h"
#include "object_manager.h"

namespace bounce {

    class InputSystem {
    private:
        const KeyboardState& keyboard_state_;
        ControlComponentCache& control_components_;
        AiComponentCache& ai_components_;
        
    public:
        InputSystem(const KeyboardState& keyboard_state, ControlComponentCache& control_components, AiComponentCache& ai_components);
        
        void Startup();
        void Shutdown();
        void Update(float delta_time);
    };

}

#endif // BOUNCE_BOUNCE_INPUT_SYSTEM_
