#ifndef BOUNCE_ENGINE_GAME_COMPONENT_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_H_

#include "bounce.h"
#include "message.h"
#include "game_component_type.h"
#include "game_entity.h"
#include "object_manager_handle.h"

namespace bounce {
    
    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
    
    class GameComponent {
    private:
        GameComponent(const GameComponent& other) = delete;
        GameComponent& operator=(const GameComponent&) = delete;
        GameComponent& operator=(GameComponent&&) = delete;

    private:
        GameComponentType component_type_;
        GameEntityHandle owner_;

    protected:
        explicit GameComponent(GameComponentType component_type, GameEntityHandle owner);
        GameComponent(GameComponent&& other) NOEXCEPT;
        
    public:
        virtual ~GameComponent() NOEXCEPT;
        
        virtual void Startup() = 0;
        
        virtual void Shutdown() = 0;
        
        virtual void Update() = 0;
        
        virtual void HandleMessage(const Message& message);
        
        void SendMessage(const Message& message) const;
        
        bool IsOfType(GameComponentType component_type);
    };
    
    inline void GameComponent::HandleMessage(const Message&)
    {
        
    }
    
    inline bool GameComponent::IsOfType(GameComponentType component_type)
    {
        return component_type_ == component_type;
    }
}

#endif // BOUNCE_ENGINE_GAME_COMPONENT_H_
