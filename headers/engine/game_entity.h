#ifndef BOUNCE_ENGINE_GAME_ENTITY_H_
#define BOUNCE_ENGINE_GAME_ENTITY_H_

#include "bounce.h"
#include "object_manager_handle.h"
#include "game_component_type.h"
#include "game_component_manager.h"
#include "message.h"

#include <vector>

namespace bounce {
    
    class GameComponent;
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class GameEntity {
    public:
        typedef std::vector<GameComponentHandle>::iterator component_iterator;
        
        static void component_manager(GameComponentManager* value);
        
        static GameEntity Create();
        
        GameEntity();
        GameEntity(GameEntity&& other) NOEXCEPT;
        
        void AttachComponent(GameComponentHandle component);
        void DetachComponent(GameComponentHandle component);
        void HandleMessage(const Message& message);
        
        GameComponentHandle GetComponentOfType(GameComponentType type);
        
    private:
        static GameComponentManager* component_manager_;
        
        std::vector<GameComponentHandle> game_components_;
        
    private:
        GameEntity(const GameEntity&) = delete;
        GameEntity& operator=(const GameEntity&) = delete;
        GameEntity& operator=(GameEntity&&) = delete;

    };
    
}

#endif // BOUNCE_ENGINE_GAME_ENTITY_H_
