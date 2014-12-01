#ifndef BOUNCE_GAME_ENTITY_H
#define BOUNCE_GAME_ENTITY_H

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
        
    public:
        static GameEntity Create();
        
        GameEntity();
        
        void AttachComponent(GameComponentHandle component);
        void DetachComponent(GameComponentHandle component);
        void HandleMessage(const Message& message);
        
        GameComponentHandle GetComponentOfType(GameComponentType type);
    };
    
}

#endif