#ifndef BOUNCE_MOVEMENT_COMPONENT_H_
#define BOUNCE_MOVEMENT_COMPONENT_H_

#include "game_component.h"
#include "game_component_type.h"
#include "framework/timer.h"

namespace bounce {
    
    class MovementComponent : public GameComponent {
    private:
        Timer& timer_;
        
        float UpdateSpeed(float delta_speed, int acceleration_direction, float speed);
        
        MovementComponent(const MovementComponent&) = delete;
        MovementComponent& operator=(const MovementComponent&) = delete;

    public:
        MovementComponent(Timer& timer);
        //MovementComponent();
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
    
    inline MovementComponent::MovementComponent(Timer& timer) : GameComponent(MOVEMENT_COMPONENT), timer_(timer) {}

//    inline MovementComponent::MovementComponent() : GameComponent(MOVEMENT_COMPONENT) {}

    
}

#endif // BOUNCE_MOVEMENT_COMPONENT_H_