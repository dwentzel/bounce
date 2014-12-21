#ifndef BOUNCE_ENGINE_BODY_COMPONENT_
#define BOUNCE_ENGINE_BODY_COMPONENT_

#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "contrib/enable_clang_warnings.h"

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
        
        glm::vec3 acceleration_;
        glm::vec3 velocity_;
        glm::vec3 position_;

        BodyComponent(GameEntityHandle owner);
        
    public:
        static BodyComponent Create(GameEntityHandle owner);
    
        void Startup();
        void Shutdown();
        void Update();
        
        virtual void HandleMessage(const Message& message);
        
        float rotation_acceleration() const;
        void rotation_acceleration(float value);
        
        float max_speed() const;
        void max_speed(float value);
        
        int yaw_acceleration_direction() const;
        void yaw_acceleration_direction(int value);
        int pitch_acceleration_direction() const;
        void pitch_acceleration_direction(int value);
        int roll_acceleration_direction() const;
        void roll_acceleration_direction(int value);
        
        float yaw_speed() const;
        void yaw_speed(float value);
        float pitch_speed() const;
        void pitch_speed(float value);
        float roll_speed() const;
        void roll_speed(float value);
        
        const glm::quat& orientation();
        void orientation(const glm::quat& value);
        
        const glm::vec3& acceleration() const;
        void acceleration(const glm::vec3& value);
        
        const glm::vec3& velocity() const;
        void velocity(const glm::vec3& value);
        
        const glm::vec3& position() const;
        void position(const glm::vec3& value);
    };
    
    inline float BodyComponent::rotation_acceleration() const
    {
        return rotation_acceleration_;
    }
    
    inline void BodyComponent::rotation_acceleration(float value)
    {
        rotation_acceleration_ = value;
    }
    
    inline float BodyComponent::max_speed() const
    {
        return max_speed_;
    }
    
    inline void BodyComponent::max_speed(float value)
    {
        max_speed_ = value;
    }
    
    inline int BodyComponent::yaw_acceleration_direction() const
    {
        return yaw_acceleration_direction_;
    }
    
    inline void BodyComponent::yaw_acceleration_direction(int value)
    {
        yaw_acceleration_direction_ = value;
    }
    
    inline int BodyComponent::pitch_acceleration_direction() const
    {
        return pitch_acceleration_direction_;
    }
    
    inline void BodyComponent::pitch_acceleration_direction(int value)
    {
        pitch_acceleration_direction_ = value;
    }
    
    inline int BodyComponent::roll_acceleration_direction() const
    {
        return roll_acceleration_direction_;
    }
    
    inline void BodyComponent::roll_acceleration_direction(int value)
    {
        roll_acceleration_direction_ = value;
    }
    
    inline float BodyComponent::yaw_speed() const
    {
        return yaw_speed_;
    }
    
    inline void BodyComponent::yaw_speed(float value)
    {
        yaw_speed_ = value;
    }
    
    inline float BodyComponent::pitch_speed() const
    {
        return pitch_speed_;
    }
    
    inline void BodyComponent::pitch_speed(float value)
    {
        pitch_speed_ = value;
    }
    
    inline float BodyComponent::roll_speed() const
    {
        return roll_speed_;
    }
    
    inline void BodyComponent::roll_speed(float value)
    {
        roll_speed_ = value;
    }
    
    inline const glm::quat& BodyComponent::orientation()
    {
        return orientation_;
    }
    
    inline void BodyComponent::orientation(const glm::quat& value)
    {
        orientation_ = value;
        
        OrientationChangedMessage message(orientation_);
        SendMessage(message);
    }

    inline const glm::vec3& BodyComponent::acceleration() const
    {
        return acceleration_;
    }
    
    inline void BodyComponent::acceleration(const glm::vec3& value)
    {
        acceleration_ = value;
    }

    
    inline const glm::vec3& BodyComponent::velocity() const
    {
        return velocity_;
    }
    
    inline void BodyComponent::velocity(const glm::vec3& value)
    {
        velocity_ = value;
    }
    
    inline const glm::vec3& BodyComponent::position() const
    {
        return position_;
    }
    
}

#endif // BOUNCE_ENGINE_BODY_COMPONENT_
