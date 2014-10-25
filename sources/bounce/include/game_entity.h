#ifndef BOUNCE_GAME_ENTITY_H
#define BOUNCE_GAME_ENTITY_H

#include <vector>

#include "game_component.h"

namespace bounce {
    
    class GameEntity {
    private:
        std::vector<GameComponent*> components_;
        
    public:
        void attachComponent(GameComponent* component);
        void detachComponent(GameComponent* component);
        void updateComponent();
        void updateComponentOfType(const GameComponentType* component_type);
        void handleMessage();
    };
    
    

}

#endif