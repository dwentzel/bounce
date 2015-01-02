#ifndef BOUNCE_ENGINE_CONTROL_COMPONENT_H_
#define BOUNCE_ENGINE_CONTROL_COMPONENT_H_

#include "game_component.h"
#include "keyboard_state.h"

namespace bounce {

    class ControlComponent : public GameComponent {
    public:
        static ControlComponent Create(const KeyboardState& keyboard_state);

        ControlComponent(ControlComponent&& other) NOEXCEPT;

        virtual void Startup();

        virtual void Shutdown();

        virtual void Update();
        
        int yaw_acceleration() const;
        int pitch_acceleration() const;
        int roll_acceleration() const;

    private:
        const KeyboardState& keyboard_state_;
        
        int yaw_acceleration_;
        int pitch_acceleration_;
        int roll_acceleration_;
    
    private:
        explicit ControlComponent(const KeyboardState& keyboard_state);
        
        ControlComponent(const ControlComponent&) = delete;
        ControlComponent& operator=(const ControlComponent&) = delete;
        ControlComponent& operator=(ControlComponent&&) = delete;
    };


}

#endif // BOUNCE_ENGINE_CONTROL_COMPONENT_H_
