#ifndef BOUNCE_MOVEMENT_COMPONENT_H_
#define BOUNCE_MOVEMENT_COMPONENT_H_

#include "game_component.h"
#include "game_component_type.h"
#include "timer.h"

namespace bounce {
    
    class MovementComponent : public GameComponent {
    private:
        const Timer& timer_;
        
        float UpdateSpeed(float delta_speed, int acceleration_direction, float speed);
        
    public:
        MovementComponent(const Timer& timer);
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
    
    inline MovementComponent::MovementComponent(const Timer& timer) : GameComponent(MOVEMENT_COMPONENT), timer_(timer) {}
    
}

#endif // BOUNCE_MOVEMENT_COMPONENT_H_