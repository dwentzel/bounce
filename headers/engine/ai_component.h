#ifndef BOUNCE_BOUNCE_AI_COMPONENT_
#define BOUNCE_BOUNCE_AI_COMPONENT_

#include "game_component.h"
#include "ai_strategy.h"

namespace bounce {

    class AiComponent : public GameComponent {
    private:
        std::unique_ptr<AiStrategy> ai_strategy_;
        
        AiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy);
        
    public:
        static AiComponent Create(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        void HandleMessage(const Message& message);
    };

}

#endif // BOUNCE_BOUNCE_AI_COMPONENT_
