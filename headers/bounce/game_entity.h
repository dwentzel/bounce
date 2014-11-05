#ifndef BOUNCE_GAME_ENTITY_H
#define BOUNCE_GAME_ENTITY_H

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "message.h"
#include "game_component_type.h"

namespace bounce {
    
    class GameComponent;
    
    typedef std::vector<GameComponent*> GameComponentList;
    
    class GameEntity {
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
        
        GameComponentList components_;
        
    public:
        GameEntity();
        
        float rotation_acceleration() const;
        float max_speed() const;
        
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
        
        void AttachComponent(GameComponent* component);
        void DetachComponent(GameComponent* component);
        void UpdateComponent();
        void UpdateComponentOfType(GameComponentType component_type);
        void HandleMessage(const Message& message);
    };
    
    typedef std::vector<GameEntity*> GameEntityList;
    
    inline float GameEntity::rotation_acceleration() const {
        return rotation_acceleration_;
    }
    
    inline float GameEntity::max_speed() const {
        return max_speed_;
    }

    inline int GameEntity::yaw_acceleration_direction() const {
        return yaw_acceleration_direction_;
    }
    
    inline void GameEntity::yaw_acceleration_direction(int acceleration_direction) {
        yaw_acceleration_direction_ = acceleration_direction;
    }
    
    inline int GameEntity::pitch_acceleration_direction() const {
        return pitch_acceleration_direction_;
    }
    
    inline void GameEntity::pitch_acceleration_direction(int acceleration_direction) {
        pitch_acceleration_direction_ = acceleration_direction;
    }
    
    inline int GameEntity::roll_acceleration_direction() const {
        return roll_acceleration_direction_;
    }
    
    inline void GameEntity::roll_acceleration_direction(int acceleration_direction) {
        roll_acceleration_direction_ = acceleration_direction;
    }
    
    inline float GameEntity::yaw_speed() const {
        return yaw_speed_;
    }

    inline void GameEntity::yaw_speed(float speed) {
        yaw_speed_ = speed;
    }
    
    inline float GameEntity::pitch_speed() const {
        return pitch_speed_;
    }
    
    inline void GameEntity::pitch_speed(float speed) {
        pitch_speed_ = speed;
    }
    
    inline float GameEntity::roll_speed() const {
        return roll_speed_;
    }
    
    inline void GameEntity::roll_speed(float speed) {
        roll_speed_ = speed;
    }
        
    inline glm::quat GameEntity::orientation() {
        return orientation_;
    }
    
    inline void GameEntity::orientation(const glm::quat& o) {
        orientation_ = o;
    }

}

#endif