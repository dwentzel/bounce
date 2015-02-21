#ifndef BOUNCE_ENGINE_AI_COMPONENT_
#define BOUNCE_ENGINE_AI_COMPONENT_

#include <memory>
#include "game_component.h"
#include "ai_strategy.h"

namespace bounce {

    class AiComponent : public GameComponent {
    public:
        static AiComponent Create(std::unique_ptr<AiStrategy> ai_strategy);

        AiComponent(AiComponent&& other) NOEXCEPT;
        virtual ~AiComponent();
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
        void HandleMessage(const Message& message);
        
    private:
        explicit AiComponent(std::unique_ptr<AiStrategy> ai_strategy);
        
        AiComponent(const AiComponent&) = delete;
        AiComponent& operator=(const AiComponent&) = delete;
        AiComponent& operator=(AiComponent&&) = delete;
        
    private:
        std::unique_ptr<AiStrategy> ai_strategy_;
    
    };

}

#endif // BOUNCE_ENGINE_AI_COMPONENT_
