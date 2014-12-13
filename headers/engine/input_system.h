#ifndef BOUNCE_ENGINE_INPUT_SYSTEM_
#define BOUNCE_ENGINE_INPUT_SYSTEM_

#include "framework/object_cache.h"
#include "game_entity.h"
#include "keyboard_state.h"

namespace bounce {

    class InputSystem {
    private:
        const KeyboardState& keyboard_state_;

        ObjectCache<GameEntity>& game_entities_;

        InputSystem& operator=(const InputSystem&) = delete;
        
    public:
        InputSystem(const KeyboardState& keyboard_state, ObjectCache<GameEntity>& game_entities);
        
        void Startup();
        void Shutdown();
        void Update(float delta_time);
    };

}

#endif // BOUNCE_ENGINE_INPUT_SYSTEM_
