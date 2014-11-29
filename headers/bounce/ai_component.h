#ifndef BOUNCE_BOUNCE_AI_COMPONENT_
#define BOUNCE_BOUNCE_AI_COMPONENT_

#include "game_component.h"
#include "ai_strategy.h"

namespace bounce {

    class AiComponent : public GameComponent {
    private:
        std::unique_ptr<AiStrategy> ai_strategy_;
        
        AiComponent(GameEntityHandle owner);
        
    public:
        static AiComponent Create(GameEntityHandle owner);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        void SetStrategy(std::unique_ptr<AiStrategy> ai_strategy);
        
        void HandleMessage(const Message& message);
    };

}

#endif // BOUNCE_BOUNCE_AI_COMPONENT_
