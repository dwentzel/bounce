#include <algorithm>
#include "game_entity.h"

#include "object_manager.h"
#include "game_component.h"

bounce::GameEntity bounce::GameEntity::Create()
{
    return GameEntity();
}

bounce::GameEntity::GameEntity()
{

}

void bounce::GameEntity::AttachComponent(bounce::GameComponentHandle handle)
{
//    game_components_.push_back(handle);
}

void bounce::GameEntity::DetachComponent(bounce::GameComponentHandle handle)
{
//    game_components_.erase(std::remove(game_components_.begin(), game_components_.end(), handle), game_components_.end());
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

//void bounce::GameEntity::UpdateComponentOfType(bounce::GameComponentType component_type) {
//    GameComponentTypePredicate predicate(component_type);
//    
////    GameComponentList::iterator result =
////    //std::find_if(components_.begin(), components_.end(), std::bind(gameComponentTypesAreEqual, component_type, std::placeholders::_1));
////    std::find_if(components_.begin(), components_.end(), predicate);
////    if (result != components_.end()) {
////        (*result)->Update();
////    }
//}
