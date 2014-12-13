#ifndef BOUNCE_ENGINE_OBJECT_MANAGER_
#define BOUNCE_ENGINE_OBJECT_MANAGER_

#include "framework/object_cache.h"
#include "object_manager_handle.h"
#include "game_entity.h"
#include "control_component.h"
#include "ai_component.h"
#include "body_component.h"

#include "render_component.h"
#include "point_light_component.h"

namespace bounce {
        
//    template <>
//    inline GameEntity& ResolveHandleAs<GameEntity>(const ObjectManagerHandle<GameEntity>& handle)
//    {
//        if (handle.type() == ObjectManager::GAME_ENTITY_TYPE) {
//            return ObjectManager::instance_.game_entities_.GetObject(handle.index());
//        }
//        
//        throw ObjectManagerHandleException();
//    }
    

    
//    template <>
//    inline ObjectManagerHandle<AiComponent> ConvertHandle<AiComponent>(const ObjectManagerHandle<GameComponent>& handle)
//    {
//        return ObjectManagerHandle<AiComponent>(AI_COMPONENT, handle.index());
//    }
}

#endif // BOUNCE_ENGINE_OBJECT_MANAGER_
