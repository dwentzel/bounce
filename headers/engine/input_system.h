#ifndef BOUNCE_ENGINE_INPUT_SYSTEM_
#define BOUNCE_ENGINE_INPUT_SYSTEM_

#include "framework/object_cache.h"
#include "game_entity.h"
#include "keyboard_state.h"

namespace bounce {

    class InputSystem {
    public:
        explicit InputSystem(ObjectCache<GameEntity>& game_entities, GameComponentManager& component_manager);
        
        void Startup();
        void Shutdown();
        void Update(float delta_time);

    private:        
        ObjectCache<GameEntity>& game_entities_;
        GameComponentManager& component_manager_;
        
    private:
        InputSystem(const InputSystem&) = delete;
        InputSystem(InputSystem&&) = delete;
        InputSystem& operator=(const InputSystem&) = delete;
        InputSystem& operator=(InputSystem&&) = delete;
    };

}

#endif // BOUNCE_ENGINE_INPUT_SYSTEM_
