#include <algorithm>
#include "game_entity.h"
#include "game_component.h"

bounce::GameEntity bounce::GameEntity::Create()
{
    return GameEntity();
}

bounce::GameEntity::GameEntity()
{

}

void bounce::GameEntity::AttachComponent(bounce::GameComponent& component)
{
//    components_.push_back(component);
//    component.AttachToEntity(this);
}

void bounce::GameEntity::DetachComponent(bounce::GameComponent& component)
{
//    components_.erase(std::remove(components_.begin(), components_.end(), component), components_.end());
}

void bounce::GameEntity::HandleMessage(const bounce::Message &message)
{
//    for (GameComponentList::iterator i = components_.begin(); i != components_.end(); ++i) {
//        (*i)->HandleMessage(message);
//    }
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
}

void bounce::GameEntity::UpdateComponentOfType(bounce::GameComponentType component_type) {
    GameComponentTypePredicate predicate(component_type);
    
//    GameComponentList::iterator result =
//    //std::find_if(components_.begin(), components_.end(), std::bind(gameComponentTypesAreEqual, component_type, std::placeholders::_1));
//    std::find_if(components_.begin(), components_.end(), predicate);
//    if (result != components_.end()) {
//        (*result)->Update();
//    }
}
