#ifndef BOUNCE_ENGINE_MOVEMENT_SYSTEM_
#define BOUNCE_ENGINE_MOVEMENT_SYSTEM_

#include "framework/object_cache.h"
#include "game_system.h"
#include "game_entity.h"
#include "body_component.h"

namespace bounce {
    
    class MovementSystem : public GameSystem {
    public:
        explicit MovementSystem(ObjectCache<GameEntity>& game_entities, GameComponentManager& component_manager);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update(float delta_time);
    
    private:
        ObjectCache<GameEntity>& game_entities_;
        GameComponentManager& component_manager_;
        
        
        float UpdateSpeed(float delta_speed, float acceleration_direction, float speed, float max_speed) const;
        void UpdateRotation(BodyComponent& component, float delta_time);
        void UpdatePosition(BodyComponent& component, float delta_time);

        static const glm::vec3 yaw_axis_;
        static const glm::vec3 pitch_axis_;
        static const glm::vec3 roll_axis_;
    private:
        MovementSystem(const MovementSystem&) = delete;
        MovementSystem(MovementSystem&&) = delete;
        MovementSystem& operator=(const MovementSystem&) = delete;
        MovementSystem& operator=(MovementSystem&&) = delete;
    };

}

#endif // BOUNCE_ENGINE_MOVEMENT_SYSTEM_
