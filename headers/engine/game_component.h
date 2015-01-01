#ifndef BOUNCE_ENGINE_GAME_COMPONENT_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_H_

#include "bounce.h"
#include "message.h"
#include "game_component_type.h"

namespace bounce {
    
    class GameEntity;
    
    class GameComponent {
    protected:
        explicit GameComponent(GameComponentType component_type);
        GameComponent(GameComponent&& other) NOEXCEPT;
        
    public:
        virtual ~GameComponent();
        
        virtual void Startup() = 0;
        
        virtual void Shutdown() = 0;
        
        virtual void Update() = 0;
        
        virtual void HandleMessage(const Message& message);
        
        bool IsOfType(GameComponentType component_type);
        
    private:
        GameComponentType component_type_;
        
    private:
        GameComponent(const GameComponent& other) = delete;
        GameComponent& operator=(const GameComponent&) = delete;
        GameComponent& operator=(GameComponent&&) = delete;
        
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
