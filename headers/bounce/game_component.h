#ifndef BOUNCE_GAME_COMPONENT_H
#define BOUNCE_GAME_COMPONENT_H

#include "message.h"
#include "game_component_type.h"
#include "game_entity.h"
#include "object_manager_handle.h"

namespace bounce {
    
    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
    
    class GameComponent {
    private:
        GameComponentType component_type_;
        GameEntityHandle owner_;
    
    protected:
        GameComponent(GameComponentType component_type, GameEntityHandle owner);
        
        GameEntity& owner();
        
    public:
        virtual ~GameComponent() = 0;
        
        virtual void Startup() = 0;
        
        virtual void Shutdown() = 0;
        
        virtual void Update() = 0;
        
        virtual void HandleMessage(const Message& message);
        
        bool IsOfType(GameComponentType component_type);
        
//        void AttachToEntity(GameEntityHandle* entity);
    };
    
    inline GameComponent::GameComponent(GameComponentType component_type, GameEntityHandle owner)
    : component_type_(component_type), owner_(owner)
    {
    }
    
    inline GameComponent::~GameComponent() {}
    
    inline GameEntity& GameComponent::owner() {
        return owner_.Resolve();
    }
    
    inline void GameComponent::HandleMessage(const Message& message) {}
    
    inline bool GameComponent::IsOfType(GameComponentType component_type) {
        return component_type_ == component_type;
    }
    
//    inline void GameComponent::AttachToEntity(GameEntityHandle* entity) {
//        owner_ = entity;
//    }
}

#endif