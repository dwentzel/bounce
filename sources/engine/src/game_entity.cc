#include "game_entity.h"

#include "game_component_manager.h"
#include "game_component.h"

#include <cassert>
#include <algorithm>


bounce::GameComponentManager* bounce::GameEntity::component_manager_;

bounce::GameEntity bounce::GameEntity::Create()
{
    return GameEntity();
}

void bounce::GameEntity::component_manager(GameComponentManager* value)
{
    component_manager_ = value;
}

bounce::GameEntity::GameEntity()
{
    assert(component_manager_ != nullptr);
}

bounce::GameEntity::GameEntity(GameEntity&& source) NOEXCEPT
    : game_components_(std::move(source.game_components_))
{

}

void bounce::GameEntity::AttachComponent(bounce::GameComponentHandle handle)
{
    game_components_.push_back(handle);
}

void bounce::GameEntity::DetachComponent(bounce::GameComponentHandle)
{
//    game_components_.erase(std::remove(game_components_.begin(), game_components_.end(), handle), game_components_.end());
}

void bounce::GameEntity::HandleMessage(const bounce::Message &message)
{
    for (std::vector<GameComponentHandle>::iterator i = game_components_.begin(); i != game_components_.end(); ++i) {
        component_manager_->ResolveHandle(*i).HandleMessage(message);
    }
}

bounce::GameComponentHandle bounce::GameEntity::GetComponentOfType(GameComponentType type)
{
    component_iterator iter = std::find_if(game_components_.begin(), game_components_.end(), [type](const GameComponentHandle& handle) {
        return handle.type() == type;
    });
    
    if (iter != game_components_.end()) {
        return *iter;
    }
    else {
        return GameComponentHandle::invalid_handle;
    }
}
