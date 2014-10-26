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
        int horizontal_acceleration_direction_;
        int vertical_acceleration_direction_;
        
        float rotation_acceleration_;
        float max_speed_;
        
        float horizontal_speed_;
        float vertical_speed_;
        float horizontal_angle_;
        float vertical_angle_;
        
        glm::quat orientation_;
        
        GameComponentList components_;
        
    public:
        GameEntity();
        
        float rotation_acceleration() const;
        float max_speed() const;
        
        int horizontal_acceleration_direction() const;
        void horizontal_acceleration_direction(int acceleration_direction);
        int vertical_acceleration_direction() const;
        void vertical_acceleration_direction(int acceleration_direction);
        
        float horizontal_speed() const;
        void horizontal_speed(float speed);
        float vertical_speed() const;
        void vertical_speed(float speed);
        float horizontal_angle() const;
        void horizontal_angle(float angle);
        float vertical_angle() const;
        void vertical_angle(float angle);
        
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

    inline int GameEntity::horizontal_acceleration_direction() const {
        return horizontal_acceleration_direction_;
    }
    
    inline void GameEntity::horizontal_acceleration_direction(int acceleration_direction) {
        horizontal_acceleration_direction_ = acceleration_direction;
    }
    
    inline int GameEntity::vertical_acceleration_direction() const {
        return vertical_acceleration_direction_;
    }
    
    inline void GameEntity::vertical_acceleration_direction(int acceleration_direction) {
        vertical_acceleration_direction_ = acceleration_direction;
    }
    
    inline float GameEntity::horizontal_speed() const {
        return horizontal_speed_;
    }

    inline void GameEntity::horizontal_speed(float speed) {
        horizontal_speed_ = speed;
    }
    
    inline float GameEntity::vertical_speed() const {
        return vertical_speed_;
    }
    
    inline void GameEntity::vertical_speed(float speed) {
        vertical_speed_ = speed;
    }
    
    inline float GameEntity::horizontal_angle() const {
        return horizontal_angle_;
    }

    inline void GameEntity::horizontal_angle(float angle) {
        horizontal_angle_ = angle;
    }
    
    inline float GameEntity::vertical_angle() const {
        return vertical_angle_;
    }
    
    inline void GameEntity::vertical_angle(float angle) {
        vertical_angle_ = angle;
    }
    
    inline glm::quat GameEntity::orientation() {
        return orientation_;
    }
    
    inline void GameEntity::orientation(const glm::quat& o) {
        orientation_ = o;
    }

}

#endif