#include "game_entity_manager.h"

bounce::GameEntityManager::GameEntityManager()
{

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
