#ifndef BOUNCE_ENGINE_AI_STRATEGY_
#define BOUNCE_ENGINE_AI_STRATEGY_

#include "message.h"

namespace bounce {

    class AiComponent;
    
    class AiStrategy {
    private:
        
    protected:
//        void SendMessage(const AiComponent& owner, const Message& message);
        
        AiStrategy();

    public:
        AiStrategy(const AiStrategy&);

        virtual ~AiStrategy();
        
        virtual void Update(const AiComponent& owner) = 0;
        
        virtual void HandleMessage(const Message& message) = 0;
    };

}

#endif // BOUNCE_ENGINE_AI_STRATEGY_
