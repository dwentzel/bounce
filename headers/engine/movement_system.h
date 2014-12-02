#ifndef BOUNCE_ENGINE_MOVEMENT_SYSTEM_
#define BOUNCE_ENGINE_MOVEMENT_SYSTEM_

#include "object_manager.h"
#include "body_component.h"

#include "game_system.h"

namespace bounce {
    
    class MovementSystem : public GameSystem {
    private:
        GameEntityCache& game_entities_;
    
        float UpdateSpeed(float delta_speed, float acceleration_direction, float speed, float max_speed) const;
        void UpdateRotation(BodyComponent& component, float delta_time);
        void UpdatePosition(BodyComponent& component, float delta_time);
        
    public:
        MovementSystem(GameEntityCache& game_entities);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);
    
    };

}

#endif // BOUNCE_ENGINE_MOVEMENT_SYSTEM_
