#ifndef BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_

#include "framework/object_cache.h"
#include "object_manager_handle.h"
#include "body_component.h"
#include "camera_component.h"
#include "control_component.h"
#include "render_component.h"
#include "point_light_component.h"

#include "exceptions.h"

namespace bounce {

    typedef ObjectCache<BodyComponent> BodyComponentCache;
    typedef ObjectCache<ControlComponent> ControlComponentCache;
    typedef ObjectCache<RenderComponent> RenderComponentCache;
    typedef ObjectCache<PointLightComponent> PointLightComponentCache;
    
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class GameComponentManager {
    public:
        GameComponentManager();
        
        BodyComponentCache& body_components();
        const BodyComponentCache& body_components() const;
        
        ControlComponentCache& control_components();
        const ControlComponentCache& control_components() const;
        
        const RenderComponentCache& render_components() const;
        const PointLightComponentCache& point_light_components() const;
        
        GameComponentHandle GenerateBodyComponent();
        GameComponentHandle GenerateControlComponent(std::unique_ptr<ControlStrategy> control_strategy);
        GameComponentHandle GenerateRenderComponent(unsigned int model_handle);
        GameComponentHandle GeneratePointLightComponent();
        
        template <typename T>
        T& ResolveHandle(const ObjectManagerHandle<T>& handle);
        
        template <typename T, typename Handle>
        T& ResolveHandleAs(const ObjectManagerHandle<Handle>& handle);

    private:
        GameComponentManager(const GameComponentManager&) = delete;
        GameComponentManager(GameComponentManager&&) = delete;
        GameComponentManager& operator=(const GameComponentManager&) = delete;
        GameComponentManager& operator=(GameComponentManager&&) = delete;
        
    private:
        BodyComponentCache body_components_;
        ControlComponentCache control_components_;
        RenderComponentCache render_components_;
        PointLightComponentCache point_light_components_;
        
    };
    
    template <>
    inline GameComponent& GameComponentManager::ResolveHandle<GameComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        unsigned int index = handle.index();
        
        switch (handle.type()) {
            case BODY_COMPONENT:
                return body_components_.GetObject(index);
            case CONTROL_COMPONENT:
                return control_components_.GetObject(index);
            case RENDER_COMPONENT:
                return render_components_.GetObject(index);
            case POINT_LIGHT_COMPONENT:
                return point_light_components_.GetObject(index);
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline BodyComponent& GameComponentManager::ResolveHandleAs<BodyComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == BODY_COMPONENT) {
            return body_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline ControlComponent& GameComponentManager::ResolveHandleAs<ControlComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == CONTROL_COMPONENT) {
            return control_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline RenderComponent& GameComponentManager::ResolveHandleAs<RenderComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == RENDER_COMPONENT) {
            return render_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline PointLightComponent& GameComponentManager::ResolveHandleAs<PointLightComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == POINT_LIGHT_COMPONENT) {
            return point_light_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }

}

#endif // BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_
