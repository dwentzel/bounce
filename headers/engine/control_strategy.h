#ifndef BOUNCE_ENGINE_CONTROL_STRATEGY_H_
#define BOUNCE_ENGINE_CONTROL_STRATEGY_H_

#include "message.h"
#include <memory>

namespace bounce {

    class ControlStrategy {
    public:
        ControlStrategy();
        ControlStrategy(ControlStrategy&& other) NOEXCEPT;
        virtual ~ControlStrategy();
        
        virtual void Update() = 0;
        virtual void HandleMessage(const Message& message);
        virtual std::unique_ptr<Message> CreateMessage() const = 0;
        
    private:
        
    };

}

#endif // BOUNCE_ENGINE_CONTROL_STRATEGY_H_
