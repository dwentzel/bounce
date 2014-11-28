#ifndef BOUNCE_BOUNCE_BODY_COMPONENT_
#define BOUNCE_BOUNCE_BODY_COMPONENT_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "framework/object_cache.h"
#include "game_component.h"

namespace bounce {

    class BodyComponent : public GameComponent {
    private:
        int yaw_acceleration_direction_;
        int pitch_acceleration_direction_;
        int roll_acceleration_direction_;
        
        float rotation_acceleration_;
        float max_speed_;
        
        float yaw_speed_;
        float pitch_speed_;
        float roll_speed_;
        
        glm::quat orientation_;
        glm::vec3 position_;

        BodyComponent(GameEntityHandle owner);
        
    public:
        static BodyComponent Create(GameEntityHandle owner);
    
        void Startup();
        void Shutdown();
        void Update();
        
        virtual void HandleMessage(const Message& message);
        
        float rotation_acceleration() const;
        void rotation_acceleration(float rotation_acceleration);
        
        float max_speed() const;
        void max_speed(float max_speed);
        
        int yaw_acceleration_direction() const;
        void yaw_acceleration_direction(int acceleration_direction);
        int pitch_acceleration_direction() const;
        void pitch_acceleration_direction(int acceleration_direction);
        int roll_acceleration_direction() const;
        void roll_acceleration_direction(int acceleration_direction);
        
        float yaw_speed() const;
        void yaw_speed(float speed);
        float pitch_speed() const;
        void pitch_speed(float speed);
        float roll_speed() const;
        void roll_speed(float speed);
        
        glm::quat orientation();
        void orientation(const glm::quat& o);
        
        glm::vec3 position() const;
        void position(const glm::vec3& position);
    };
    
    inline float BodyComponent::rotation_acceleration() const
    {
        return rotation_acceleration_;
    }
    
    inline void BodyComponent::rotation_acceleration(float rotation_acceleration)
    {
        rotation_acceleration_ = rotation_acceleration;
    }
    
    inline float BodyComponent::max_speed() const
    {
        return max_speed_;
    }
    
    inline void BodyComponent::max_speed(float max_speed)
    {
        max_speed_ = max_speed;
    }
    
    inline int BodyComponent::yaw_acceleration_direction() const
    {
        return yaw_acceleration_direction_;
    }
    
    inline void BodyComponent::yaw_acceleration_direction(int acceleration_direction)
    {
        yaw_acceleration_direction_ = acceleration_direction;
    }
    
    inline int BodyComponent::pitch_acceleration_direction() const
    {
        return pitch_acceleration_direction_;
    }
    
    inline void BodyComponent::pitch_acceleration_direction(int acceleration_direction)
    {
        pitch_acceleration_direction_ = acceleration_direction;
    }
    
    inline int BodyComponent::roll_acceleration_direction() const
    {
        return roll_acceleration_direction_;
    }
    
    inline void BodyComponent::roll_acceleration_direction(int acceleration_direction)
    {
        roll_acceleration_direction_ = acceleration_direction;
    }
    
    inline float BodyComponent::yaw_speed() const
    {
        return yaw_speed_;
    }
    
    inline void BodyComponent::yaw_speed(float speed)
    {
        yaw_speed_ = speed;
    }
    
    inline float BodyComponent::pitch_speed() const
    {
        return pitch_speed_;
    }
    
    inline void BodyComponent::pitch_speed(float speed)
    {
        pitch_speed_ = speed;
    }
    
    inline float BodyComponent::roll_speed() const
    {
        return roll_speed_;
    }
    
    inline void BodyComponent::roll_speed(float speed)
    {
        roll_speed_ = speed;
    }
    
    inline glm::quat BodyComponent::orientation()
    {
        return orientation_;
    }
    
    inline void BodyComponent::orientation(const glm::quat& o)
    {
        orientation_ = o;
        
        OrientationChangedMessage message(orientation_);
        owner().HandleMessage(message);
    }
    
    inline glm::vec3 BodyComponent::position() const
    {
        return position_;
    }
    
    inline void BodyComponent::position(const glm::vec3& position)
    {
        position_ = position;
    }

    typedef ObjectCache<BodyComponent> BodyComponentCache;


}

#endif // BOUNCE_BOUNCE_BODY_COMPONENT_
