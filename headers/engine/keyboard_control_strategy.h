#ifndef BOUNCE_ENGINE_KEYBOARD_CONTROL_STRATEGY_H_
#define BOUNCE_ENGINE_KEYBOARD_CONTROL_STRATEGY_H_

#include "control_strategy.h"
#include "bounce.h"
#include "keyboard_state.h"

namespace bounce {

    class KeyboardControlStrategy : public ControlStrategy {
    public:
        KeyboardControlStrategy(const KeyboardState& keyboard_state);
        KeyboardControlStrategy(KeyboardControlStrategy&& other) NOEXCEPT;
        
        virtual void Update();
        virtual std::unique_ptr<Message> CreateMessage() const;
        
        int yaw_acceleration() const;
        int pitch_acceleration() const;
        int roll_acceleration() const;
        
    private:
        const KeyboardState& keyboard_state_;
        
        int yaw_acceleration_;
        int pitch_acceleration_;
        int roll_acceleration_;

    };

}

#endif // BOUNCE_ENGINE_KEYBOARD_CONTROL_STRATEGY_H_
