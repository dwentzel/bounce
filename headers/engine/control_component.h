#ifndef BOUNCE_ENGINE_CONTROL_COMPONENT_H_
#define BOUNCE_ENGINE_CONTROL_COMPONENT_H_

#include "game_component.h"
#include "control_strategy.h"
#include "keyboard_state.h"

namespace bounce {

    class ControlComponent : public GameComponent {
    public:
        static ControlComponent Create(std::unique_ptr<ControlStrategy> control_strategy);

        ControlComponent(ControlComponent&& other) NOEXCEPT;

        virtual void Startup();

        virtual void Shutdown();

        virtual void Update();
        
        std::shared_ptr<Message> CreateMessage() const;

    private:
        std::unique_ptr<ControlStrategy> control_strategy_;
    
    private:
        explicit ControlComponent(std::unique_ptr<ControlStrategy> control_strategy);
        
        ControlComponent(const ControlComponent&) = delete;
        ControlComponent& operator=(const ControlComponent&) = delete;
        ControlComponent& operator=(ControlComponent&&) = delete;
    };


}

#endif // BOUNCE_ENGINE_CONTROL_COMPONENT_H_
