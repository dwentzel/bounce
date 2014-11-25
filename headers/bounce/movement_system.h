#ifndef BOUNCE_BOUNCE_MOVEMENT_SYSTEM_
#define BOUNCE_BOUNCE_MOVEMENT_SYSTEM_

#include "framework/object_cache.h"
#include "body_component.h"

#include "game_system.h"

namespace bounce {

    class MovementSystem : public GameSystem {
    private:
        BodyComponentCache& body_components_;
    
        float UpdateSpeed(float delta_speed, float acceleration_direction, float speed, float max_speed) const;
        
    public:
        MovementSystem(BodyComponentCache& body_components);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);
    
    };

}

#endif // BOUNCE_BOUNCE_MOVEMENT_SYSTEM_
