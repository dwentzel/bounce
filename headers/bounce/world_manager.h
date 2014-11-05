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
        WorldManager();
        void AddEntity(GameEntity* entity);
        const std::vector<GameEntity*>& entities() const;
    };
    
    inline WorldManager::WorldManager() {}
    
    inline void WorldManager::AddEntity(GameEntity* entity) {
        game_entities_.push_back(entity);
    }
    
    inline const std::vector<GameEntity*>& WorldManager::entities() const {
        return game_entities_;
    }
    
}

#endif