#ifndef BOUNCE_WORLD_MANAGER_H
#define BOUNCE_WORLD_MANAGER_H

#include <vector>
#include "game_system.h"
#include "game_entity.h"

namespace bounce {
    
    class WorldManager {
    private:
        std::vector<GameEntity*> game_entities_;
        
    public:
        void addEntity(GameEntity* entity);
        const std::vector<GameEntity*>& entities() const;
    };
    
    inline void WorldManager::addEntity(GameEntity* entity) {
        game_entities_.insert(game_entities_.end(), entity);
    }
    
    inline const std::vector<GameEntity*>& WorldManager::entities() const {
        return game_entities_;
    }
    
}

#endif