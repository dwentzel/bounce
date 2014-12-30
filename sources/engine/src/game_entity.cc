#include <algorithm>
#include "game_entity.h"

#include "game_component_manager.h"
#include "game_component.h"

bounce::GameEntity bounce::GameEntity::Create()
{
    return GameEntity();
}

bounce::GameEntity::GameEntity()
{

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
        ResolveHandle(*i).HandleMessage(message);
    }
}
