#include <functional>
#include "game_entity.h"
#include "game_component.h"

bounce::GameEntity::GameEntity() : horizontal_acceleration_direction_(0), vertical_acceleration_direction_(0), rotation_acceleration_(0.0202f), max_speed_(0.1f), horizontal_speed_(0.0f), vertical_speed_(0.0f), horizontal_angle_(0.0f), vertical_angle_(0.0f) {
    //orientation_ = glm::quat(1, 1, 0.6, 0.9);
    
    horizontal_angle_ = 0.0f;
    vertical_angle_ = 0.0f;
    
    glm::quat horizontal = glm::angleAxis(horizontal_angle_, glm::normalize(glm::vec3(0.0f, cos(vertical_angle_), sin(vertical_angle_))));

    orientation_ = horizontal;
    
    //orientation_ = glm::quat(1, 0, 0, 0);
}

void bounce::GameEntity::AttachComponent(bounce::GameComponent* component) {
    components_.push_back(component);
    component->AttachToEntity(this);
}

void bounce::GameEntity::DetachComponent(bounce::GameComponent* component) {
    components_.erase(std::remove(components_.begin(), components_.end(), component), components_.end());
}

void bounce::GameEntity::HandleMessage(const bounce::Message &message) {
    for (GameComponentList::iterator i = components_.begin(); i != components_.end(); ++i) {
        (*i)->HandleMessage(message);
    }
}

namespace {
    
    class GameComponentTypePredicate {
    private:
        bounce::GameComponentType type_;
        
    public:
        GameComponentTypePredicate(bounce::GameComponentType type) : type_(type) {}
        
        inline bool operator()(bounce::GameComponent* component) const {
            return component->IsOfType(type_);
        }
    };
    
    //bool gameComponentTypesAreEqual(const bounce::GameComponentType* type1, const bounce::GameComponentType* type2) {
    //    return type1 == type2;
    //}
    
}

void bounce::GameEntity::UpdateComponentOfType(bounce::GameComponentType component_type) {
    GameComponentTypePredicate predicate(component_type);
    
    GameComponentList::iterator result =
    //std::find_if(components_.begin(), components_.end(), std::bind(gameComponentTypesAreEqual, component_type, std::placeholders::_1));
    std::find_if(components_.begin(), components_.end(), predicate);
    if (result != components_.end()) {
        (*result)->Update();
    }
}
