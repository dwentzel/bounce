#ifndef BOUNCE_BOUNCE_OBJECT_MANAGER_
#define BOUNCE_BOUNCE_OBJECT_MANAGER_

#include "framework/object_cache.h"
#include "game_entity.h"
#include "body_component.h"
#include "render_component.h"
#include "point_light_component.h"

namespace bounce {
    
    class ObjectManagerHandleException : public std::exception {
        
    };
    
    template <typename T>
    class ObjectManagerHandle;
    
    typedef ObjectCache<BodyComponent> BodyComponentCache;
    typedef ObjectCache<RenderComponent> RenderComponentCache;
    typedef ObjectCache<PointLightComponent> PointLightComponentCache;
    
    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class ObjectManager {
    private:
        ObjectCache<GameEntity> game_entities_;
        BodyComponentCache body_components_;
        RenderComponentCache render_components_;
        PointLightComponentCache point_light_components_;
        
    public:
        
        enum ObjectType {
            GAME_ENTITY_TYPE,
            BODY_COMPONENT_TYPE,
            RENDER_COMPONENT_TYPE,
            POINT_LIGHT_COMPONENT_TYPE
        };

        const ObjectCache<GameEntity>& game_entities() const;

        BodyComponentCache& body_components();
        const BodyComponentCache& body_components() const;
        
        const RenderComponentCache& render_components() const;

        const PointLightComponentCache& point_light_components() const;
        
        GameEntityHandle GenerateGameEntity();
        GameComponentHandle GenerateBodyComponent();
        GameComponentHandle GenerateRenderComponent(unsigned int model_handle);
        GameComponentHandle GeneratePointLightComponent();
        
        GameEntity& GetGameEntity(unsigned int handle);
        BodyComponent& GetBodyComponent(unsigned int handle);
        RenderComponent& GetRenderComponent(unsigned int handle);
        PointLightComponent& GetPointLightComponent(unsigned int handle);
        
        template <typename T>
        T& ResolveHandle(ObjectManagerHandle<T>& handle);
        
        template <typename T, typename Handle>
        T& ResolveHandleAs(ObjectManagerHandle<Handle>& handle);
        
    };
    
    template <typename T>
    class ObjectManagerHandle {
    private:
        unsigned int index_;
        ObjectManager::ObjectType type_;
        
        ObjectManager& object_manager_;
        
    public:
        ObjectManagerHandle(ObjectManager& object_manager, ObjectManager::ObjectType type, unsigned int index)
        :  index_(index), type_(type), object_manager_(object_manager)
        {
            
        }
        
        unsigned int index() const
        {
            return index_;
        }
        
        ObjectManager::ObjectType type() const
        {
            return type_;
        }
        
        T& Resolve()
        {
            return object_manager_.ResolveHandle<T>(*this);
        }
        
        template <typename S>
        S& ResolveAs()
        {
            return object_manager_.ResolveHandleAs<S, T>(*this);
        }
    };
    
    template <>
    inline GameEntity& ObjectManager::ResolveHandle<GameEntity>(ObjectManagerHandle<GameEntity>& handle)
    {
        if (handle.type() == ObjectManager::GAME_ENTITY_TYPE) {
            return game_entities_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline GameEntity& ObjectManager::ResolveHandleAs<GameEntity>(ObjectManagerHandle<GameEntity>& handle)
    {
        if (handle.type() == ObjectManager::GAME_ENTITY_TYPE) {
            return game_entities_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline BodyComponent& ObjectManager::ResolveHandleAs<BodyComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == ObjectManager::BODY_COMPONENT_TYPE) {
            return body_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline RenderComponent& ObjectManager::ResolveHandleAs<RenderComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == ObjectManager::RENDER_COMPONENT_TYPE) {
            return render_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline PointLightComponent& ObjectManager::ResolveHandleAs<PointLightComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == ObjectManager::POINT_LIGHT_COMPONENT_TYPE) {
            return point_light_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
}

#endif // BOUNCE_BOUNCE_OBJECT_MANAGER_
