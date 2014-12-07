#ifndef BOUNCE_ENGINE_AI_COMPONENT_
#define BOUNCE_ENGINE_AI_COMPONENT_

#include <memory>
#include "game_component.h"
#include "ai_strategy.h"

namespace bounce {

    class AiComponent : public GameComponent {
    private:
        std::unique_ptr<AiStrategy> ai_strategy_;
        
        AiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy);
        
        AiComponent(const AiComponent&) = delete;
        AiComponent& operator=(const AiComponent&) = delete;

    public:
        static AiComponent Create(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy);

        AiComponent(AiComponent&& source);
        ~AiComponent();
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        void HandleMessage(const Message& message);
    };

}

#endif // BOUNCE_ENGINE_AI_COMPONENT_
