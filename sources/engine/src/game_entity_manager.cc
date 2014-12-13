#include "game_entity_manager.h"

bounce::GameEntityManager bounce::GameEntityManager::instance_;

bounce::GameEntityManager& bounce::GameEntityManager::instance()
{
    return instance_;
}

bounce::GameEntityCache& bounce::GameEntityManager::game_entities()
{
    return game_entities_;
}

const bounce::GameEntityCache& bounce::GameEntityManager::game_entities() const
{
    return game_entities_;
}

bounce::GameEntityHandle bounce::GameEntityManager::GenerateGameEntity()
{
    unsigned int index = game_entities_.GenerateObject();
    return GameEntityHandle(0, index);
}
