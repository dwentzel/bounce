#ifndef BOUNCE_BOUNCE_OBJECT_MANAGER_
#define BOUNCE_BOUNCE_OBJECT_MANAGER_

#include "framework/object_cache.h"
#include "game_entity.h"
#include "body_component.h"
#include "render_component.h"
#include "point_light_component.h"

namespace bounce {
    
    template <typename T>
    class ObjectManagerHandle;

    typedef ObjectManagerHandle<GameEntity> GameEntityHandle;
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class ObjectManager {
    private:
        ObjectCache<GameEntity> game_entities_;
        BodyComponentCache body_components_;
        RenderComponentCache render_components_;
        PointLightComponentCache point_light_components_;
        
    public:

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
        unsigned int type_;
        
        ObjectManager& object_manager_;
    public:
        
        ObjectManagerHandle(ObjectManager& object_manager, unsigned int type, unsigned int index)
        : object_manager_(object_manager), type_(type), index_(index)
        {
            
        }
        
        unsigned int index() const
        {
            return index_;
        }
        
        unsigned int type() const
        {
            return type_;
        }
        
        T& Resolve()
        {
            T& result = object_manager_.ResolveHandle<T>(*this);
            return result;
        }
        
        template <typename S>
        S& ResolveAs()
        {
            S& result = object_manager_.ResolveHandleAs<S, T>(*this);
            return result;
        }
    };
    
    template <typename T>
    T& ObjectManager::ResolveHandle(ObjectManagerHandle<T>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();
        
        if (type == 0) {
            // throw error
        }
        if (type == 1) {
            return body_components_.GetObject(index);
        }
        if (type == 2) {
            return render_components_.GetObject(index);
        }
        if (type == 3) {
            return point_light_components_.GetObject(index);
        }
        
        // throw error
    }
    
    template <>
    GameEntity& ObjectManager::ResolveHandle<GameEntity>(ObjectManagerHandle<GameEntity>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();
        
        if (type == 0) {
            return game_entities_.GetObject(index);
        }
    }
    
    template <typename T, typename Handle>
    T& ObjectManager::ResolveHandleAs(ObjectManagerHandle<Handle>& handle)
    {
        //1 = 0;
        // throw error
    }
    
    template <>
    GameEntity& ObjectManager::ResolveHandleAs<GameEntity>(ObjectManagerHandle<GameEntity>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();
        
        if (type == 0) {
            return game_entities_.GetObject(index);
        }
        
        // throw error
    }
    
    template <>
    BodyComponent& ObjectManager::ResolveHandleAs<BodyComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();

        if (type == 1) {
            return body_components_.GetObject(index);
        }
        
        // throw error
    }
    
    template <>
    RenderComponent& ObjectManager::ResolveHandleAs<RenderComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();
        
        if (type == 2) {
            return render_components_.GetObject(index);
        }
        
        // throw error
    }
    
    template <>
    PointLightComponent& ObjectManager::ResolveHandleAs<PointLightComponent>(ObjectManagerHandle<GameComponent>& handle)
    {
        unsigned int type = handle.type();
        unsigned int index = handle.index();
        
        if (type == 3) {
            return point_light_components_.GetObject(index);
        }
        
        // throw error
    }

    inline const ObjectCache<GameEntity>& ObjectManager::game_entities() const
    {
        return game_entities_;
    }

    inline BodyComponentCache& ObjectManager::body_components()
    {
        return body_components_;
    }
    
    inline const BodyComponentCache& ObjectManager::body_components() const
    {
        return body_components_;
    }
    
    inline const RenderComponentCache& ObjectManager::render_components() const
    {
        return render_components_;
    }

    inline const PointLightComponentCache& ObjectManager::point_light_components() const
    {
        return point_light_components_;
    }


    inline GameEntityHandle ObjectManager::GenerateGameEntity()
    {
        unsigned int index = game_entities_.GenerateObject();
        return GameEntityHandle(*this, 0, index);
    }
    
    inline GameComponentHandle ObjectManager::GenerateBodyComponent()
    {
        unsigned int index = body_components_.GenerateObject();
        return GameComponentHandle(*this, 1, index);
    }
    
    inline GameComponentHandle ObjectManager::GenerateRenderComponent(unsigned int model_handle)
    {
        unsigned int index = render_components_.GenerateObject(model_handle);
        return GameComponentHandle(*this, 2, index);
    }
    
    inline GameComponentHandle ObjectManager::GeneratePointLightComponent()
    {
        unsigned int index = point_light_components_.GenerateObject();
        return GameComponentHandle(*this, 3, index);
    }
    
    inline GameEntity& ObjectManager::GetGameEntity(unsigned int handle)
    {
        return game_entities_.GetObject(handle);
    }

    inline BodyComponent& ObjectManager::GetBodyComponent(unsigned int handle)
    {
        return body_components_.GetObject(handle);
    }
    
    inline RenderComponent& ObjectManager::GetRenderComponent(unsigned int handle)
    {
        return render_components_.GetObject(handle);
    }
    
    inline PointLightComponent& ObjectManager::GetPointLightComponent(unsigned int handle)
    {
        return point_light_components_.GetObject(handle);
    }
}

#endif // BOUNCE_BOUNCE_OBJECT_MANAGER_
