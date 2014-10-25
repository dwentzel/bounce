#include <functional>
#include "game_entity.h"

void bounce::GameEntity::attachComponent(bounce::GameComponent* component) {
    components_.push_back(component);
}

void bounce::GameEntity::detachComponent(bounce::GameComponent* component) {
    components_.erase(std::remove(components_.begin(), components_.end(), component), components_.end());
}

class GameComponentTypePredicate {
private:
    const bounce::GameComponentType* type_;

public:
    GameComponentTypePredicate(const bounce::GameComponentType*& type) : type_(type) {}
    
    inline bool operator()(bounce::GameComponent* component) const {
        return type_ == component->component_type();
    }
};

//bool gameComponentTypesAreEqual(const bounce::GameComponentType* type1, const bounce::GameComponentType* type2) {
//    return type1 == type2;
//}

void bounce::GameEntity::updateComponentOfType(const bounce::GameComponentType* component_type) {
    GameComponentTypePredicate predicate(component_type);
    
    //predicate(component_type);
    
    std::vector<GameComponent*>::iterator result =
    //std::find_if(components_.begin(), components_.end(), std::bind(gameComponentTypesAreEqual, component_type, std::placeholders::_1));
    std::find_if(components_.begin(), components_.end(), predicate);
    if (result != components_.end()) {
        (*result)->update();
    }
}
