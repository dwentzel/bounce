#ifndef BOUNCE_ENGINE_ENTITY_MANAGER_H_
#define BOUNCE_ENGINE_ENTITY_MANAGER_H_

#include "framework/object_cache.h"

namespace bounce {

//    class GameEntity;
//    
//    typedef ObjectCache<GameEntity> GameEntityCache;
//    
//    template <class T> class ObjectManagerHandle;
//    
//    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
//    
//    
//    class EntityManager {
//    private:
//        static EntityManager instance_;
//        GameEntityCache game_entities_;
//        
//    public:
//        static EntityManager& instance();
//        
//        GameEntityCache& game_entities();
//        const GameEntityCache& game_entities() const;
//        
//        GameEntityHandle GenerateGameEntity();
//        
//        template <typename T>
//        friend T& ResolveHandle(const ObjectManagerHandle<T>& handle);
//        
//        template <typename T, typename Handle>
//        friend T& ResolveHandleAs(const ObjectManagerHandle<Handle>& handle);
//    };
//    
//    template <>
//    inline GameEntity& ResolveHandle<GameEntity>(const ObjectManagerHandle<GameEntity>& handle)
//    {
//        if (handle.type() == 0) {
//            return EntityManager::instance_.game_entities_.GetObject(handle.index());
//        }
//        
//        throw ObjectManagerHandleException();
//    }

}

#endif // BOUNCE_ENGINE_ENTITY_MANAGER_H_
