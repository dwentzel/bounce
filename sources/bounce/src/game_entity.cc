#include <functional>
#include "game_entity.h"

bounce::GameEntity::GameEntity() {
    //orientation_ = glm::quat(1, 1, 0.6, 0.9);
    
    float horizontal_angle = 1.7f;
    float vertical_angle = 2.0f;
    
    glm::quat horizontal = glm::angleAxis(horizontal_angle, glm::normalize(glm::vec3(0.0f, cos(vertical_angle), sin(vertical_angle))));

    orientation_ = horizontal;
    
    //orientation_ = glm::quat(1, 0, 0, 0);
}

void bounce::GameEntity::AttachComponent(bounce::GameComponent* component) {
    components_.push_back(component);
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
