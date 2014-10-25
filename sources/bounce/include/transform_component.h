#ifndef BOUNCE_TRANSFORM_COMPONENT_H_
#define BOUNCE_TRANSFORM_COMPONENT_H_

#include "game_component.h"

namespace bounce {
    
    class TransformComponent : public GameComponent {
    private:
        int horizontal_acceleration_direction_;
        int vertical_acceleration_direction_;
        
        float rotation_acceleration_;
        float max_speed_;
        
        float horizontal_speed_;
        float vertical_speed_;
        float horizontal_angle_;
        float vertical_angle_;
        
    public:
        TransformComponent();
        
        virtual void Startup();
        
        virtual void Shutdown();
        
        virtual void Update();
    };
    
    inline TransformComponent::TransformComponent() : GameComponent(TRANSFORM_COMPONENT), horizontal_acceleration_direction_(0), vertical_acceleration_direction_(0), rotation_acceleration_(0.0002f), max_speed_(0.1f), horizontal_speed_(0.0f), vertical_speed_(0.0f), horizontal_angle_(0.0f),
        vertical_angle_(0.0f) {}
}

#endif