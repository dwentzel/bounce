#ifndef BOUNCE_GAME_ENTITY_H
#define BOUNCE_GAME_ENTITY_H

#include <vector>

#include "framework/object_cache.h"
#include "game_component_type.h"
#include "message.h"


namespace bounce {
    
    class GameComponent;
    
    class GameEntity {
    private:
        
    public:
        static GameEntity Create();
        
        GameEntity();
        
        void AttachComponent(GameComponent& component);
        void DetachComponent(GameComponent& component);
        void UpdateComponent();
        void UpdateComponentOfType(GameComponentType component_type);
        void HandleMessage(const Message& message);
    };
    
    typedef ObjectCache<GameEntity> GameEntityCache;
//    typedef ObjectCacheHandle<GameEntity> GameEntityHandle;
    
}

#endif