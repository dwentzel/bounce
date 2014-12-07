#ifndef BOUNCE_ENGINE_GAME_ENTITY_H_
#define BOUNCE_ENGINE_GAME_ENTITY_H_

#include <vector>

#include "game_component_type.h"
#include "message.h"

namespace bounce {
    
    template <typename T>
    class ObjectManagerHandle;
    class GameComponent;
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class GameEntity {
    private:
        std::vector<GameComponentHandle> game_components_;
        
        GameEntity(const GameEntity&) = delete;
        GameEntity& operator=(const GameEntity&) = delete;

    public:
        static GameEntity Create();
        
        GameEntity();
        GameEntity(GameEntity&& source);
        
        void AttachComponent(GameComponentHandle component);
        void DetachComponent(GameComponentHandle component);
        void HandleMessage(const Message& message);
        
        GameComponentHandle GetComponentOfType(GameComponentType type);
    };
    
}

#endif // BOUNCE_ENGINE_GAME_ENTITY_H_