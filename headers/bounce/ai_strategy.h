#ifndef BOUNCE_BOUNCE_AI_STRATEGY_
#define BOUNCE_BOUNCE_AI_STRATEGY_

#include "message.h"
#include "object_manager_handle.h"

namespace bounce {

    class AiComponent;
    
    class AiStrategy {
    private:
        
    protected:
        //AiStrategy(ObjectManagerHandle<AiComponent> owner);

        void SendMessage(const AiComponent& owner, const Message& message);
        
    public:
        virtual ~AiStrategy() = 0;
        
        virtual void Update(const AiComponent& owner) = 0;
        
        virtual void HandleMessage(const Message& message) = 0;
    };

}

#endif // BOUNCE_BOUNCE_AI_STRATEGY_
