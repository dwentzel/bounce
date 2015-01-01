#ifndef BOUNCE_ENGINE_GAME_ENTITY_MANAGER_H_
#define BOUNCE_ENGINE_GAME_ENTITY_MANAGER_H_

#include "framework/object_cache.h"
#include "object_manager_handle.h"
#include "game_entity.h"

#include "exceptions.h"

namespace bounce {

    typedef ObjectCache<GameEntity> GameEntityCache;
    
    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
    
    
    class GameEntityManager {
    private:
        GameEntityManager(const GameEntityManager&) = delete;
        GameEntityManager(GameEntityManager&&) = delete;
        GameEntityManager& operator=(const GameEntityManager&) = delete;
        GameEntityManager& operator=(GameEntityManager&&) = delete;

    private:
        static GameEntityManager instance_;
        GameEntityCache game_entities_;
        
        GameEntityManager();

    public:
        static GameEntityManager& instance();
        
        GameEntityCache& game_entities();
        const GameEntityCache& game_entities() const;
        
        GameEntityHandle GenerateGameEntity();
        
        template <typename T>
        T& ResolveHandle(const ObjectManagerHandle<T>& handle);
        
        template <typename T, typename Handle>
        T& ResolveHandleAs(const ObjectManagerHandle<Handle>& handle);
    };
    
//    template <class T>
//    T& ResolveHandle(const ObjectManagerHandle<T>&);
//    
//    template <class T, class Handle>
//    T& ResolveHandleAs(const ObjectManagerHandle<Handle>&);
    
    template <>
    inline GameEntity& GameEntityManager::ResolveHandle<GameEntity>(const ObjectManagerHandle<GameEntity>& handle)
    {
        if (handle.type() == 0) {
            return GameEntityManager::instance_.game_entities_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }

}

#endif // BOUNCE_ENGINE_GAME_ENTITY_MANAGER_H_
