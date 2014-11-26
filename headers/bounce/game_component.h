#ifndef BOUNCE_GAME_COMPONENT_H
#define BOUNCE_GAME_COMPONENT_H

#include "message.h"
#include "game_component_type.h"
#include "game_entity.h"

namespace bounce {
    
    class GameComponent {
    private:
        GameComponentType component_type_;
        GameEntity* owner_;
    
    protected:
        GameComponent(GameComponentType component_type);
        
        GameEntity* owner();
        
    public:
        virtual ~GameComponent() = 0;
        
        virtual void Startup() = 0;
        
        virtual void Shutdown() = 0;
        
        virtual void Update() = 0;
        
        virtual void HandleMessage(const Message& message);
        
        bool IsOfType(GameComponentType component_type);
        
        void AttachToEntity(GameEntity* entity);
    };
    
//    inline GameComponent::GameComponent(GameComponent&& component)
//    {
//        
//    }
    
    inline GameComponent::GameComponent(GameComponentType component_type) : component_type_(component_type) {}
    
    inline GameComponent::~GameComponent() {}
    
    inline GameEntity* GameComponent::owner() {
        return owner_;
    }
    
    inline void GameComponent::HandleMessage(const Message& message) {}
    
    inline bool GameComponent::IsOfType(GameComponentType component_type) {
        return component_type_ == component_type;
    }
    
    inline void GameComponent::AttachToEntity(GameEntity* entity) {
        owner_ = entity;
    }
}

#endif