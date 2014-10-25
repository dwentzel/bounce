#ifndef BOUNCE_GAME_COMPONENT_H
#define BOUNCE_GAME_COMPONENT_H

#include "message.h"

namespace bounce {

    enum GameComponentType {
        RENDER_COMPONENT,
        TRANSFORM_COMPONENT
    };
    
    class GameComponent {
    private:
        GameComponentType component_type_;
    
    protected:
        GameComponent(GameComponentType component_type);
    
    public:
        virtual ~GameComponent() = 0;
        
        virtual void Startup() = 0;
        
        virtual void Shutdown() = 0;
        
        virtual void Update() = 0;
        
        virtual void HandleMessage(const Message& message);
        
        bool IsOfType(GameComponentType component_type);
    };
    
    inline GameComponent::GameComponent(GameComponentType component_type) : component_type_(component_type) {}
    
    inline GameComponent::~GameComponent() {}
    
    inline void GameComponent::HandleMessage(const Message& message) {}
    
    inline bool GameComponent::IsOfType(GameComponentType component_type) {
        return component_type_ == component_type;
    }
}

#endif