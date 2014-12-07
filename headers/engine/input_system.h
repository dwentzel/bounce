#ifndef BOUNCE_ENGINE_INPUT_SYSTEM_
#define BOUNCE_ENGINE_INPUT_SYSTEM_

#include "keyboard_state.h"
#include "object_manager.h"

namespace bounce {

    class InputSystem {
    private:
        const KeyboardState& keyboard_state_;

        GameEntityCache& game_entities_;

        InputSystem& operator=(const InputSystem&) = delete;
        
    public:
        InputSystem(const KeyboardState& keyboard_state, GameEntityCache& game_entities);
        
        void Startup();
        void Shutdown();
        void Update(float delta_time);
    };

}

#endif // BOUNCE_ENGINE_INPUT_SYSTEM_
