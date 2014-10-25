#ifndef BOUNCE_GAME_ENTITY_H
#define BOUNCE_GAME_ENTITY_H

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "message.h"
#include "game_component.h"

namespace bounce {
    
    typedef std::vector<GameComponent*> GameComponentList;
    
    class GameEntity {
    private:
        glm::quat orientation_;
        
        GameComponentList components_;
        
    public:
        GameEntity();
        
        glm::quat orientation();
        
        void AttachComponent(GameComponent* component);
        void DetachComponent(GameComponent* component);
        void UpdateComponent();
        void UpdateComponentOfType(GameComponentType component_type);
        void HandleMessage(const Message& message);
    };
    
    inline glm::quat GameEntity::orientation() {
        return orientation_;
    }

}

#endif