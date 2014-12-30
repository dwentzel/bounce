#ifndef BOUNCE_ENGINE_MOVEMENT_SYSTEM_
#define BOUNCE_ENGINE_MOVEMENT_SYSTEM_

#include "framework/object_cache.h"
#include "game_system.h"
#include "game_entity.h"
#include "body_component.h"

namespace bounce {
    
    class MovementSystem : public GameSystem {
    private:
        MovementSystem(const MovementSystem&) = delete;
        MovementSystem(MovementSystem&&) = delete;
        MovementSystem& operator=(const MovementSystem&) = delete;
        MovementSystem& operator=(MovementSystem&&) = delete;

    private:
        ObjectCache<GameEntity>& game_entities_;
    
        float UpdateSpeed(float delta_speed, float acceleration_direction, float speed, float max_speed) const;
        void UpdateRotation(BodyComponent& component, float delta_time);
        void UpdatePosition(BodyComponent& component, float delta_time);

    public:
        explicit MovementSystem(ObjectCache<GameEntity>& game_entities);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);
    
    };

}

#endif // BOUNCE_ENGINE_MOVEMENT_SYSTEM_
