#ifndef BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_
#define BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_

#include "framework/object_cache.h"
#include "object_manager_handle.h"
#include "body_component.h"
#include "camera_component.h"
#include "control_component.h"
#include "ai_component.h"
#include "render_component.h"
#include "point_light_component.h"

#include "exceptions.h"

namespace bounce {

    typedef ObjectCache<BodyComponent> BodyComponentCache;
    typedef ObjectCache<ControlComponent> ControlComponentCache;
    typedef ObjectCache<AiComponent> AiComponentCache;
    typedef ObjectCache<RenderComponent> RenderComponentCache;
    typedef ObjectCache<PointLightComponent> PointLightComponentCache;
    
    typedef ObjectManagerHandle<GameComponent> GameComponentHandle;
    
    class GameComponentManager {
    private:
        GameComponentManager(const GameComponentManager&) = delete;
        GameComponentManager(GameComponentManager&&) = delete;
        GameComponentManager& operator=(const GameComponentManager&) = delete;
        GameComponentManager& operator=(GameComponentManager&&) = delete;

    private:
        static GameComponentManager instance_;
        
        BodyComponentCache body_components_;
        ControlComponentCache control_components_;
        AiComponentCache ai_components_;
        RenderComponentCache render_components_;
        PointLightComponentCache point_light_components_;
        
        GameComponentManager();

    public:
        static GameComponentManager& instance();
        
        BodyComponentCache& body_components();
        const BodyComponentCache& body_components() const;
        
        ControlComponentCache& control_components();
        const ControlComponentCache& control_components() const;
        
        AiComponentCache& ai_components();
        const AiComponentCache& ai_components() const;
        
        const RenderComponentCache& render_components() const;
        const PointLightComponentCache& point_light_components() const;
        
        GameComponentHandle GenerateBodyComponent(GameEntityHandle owner);
        GameComponentHandle GenerateControlComponent(GameEntityHandle owner, const KeyboardState& keyboard_state);
        GameComponentHandle GenerateAiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy);
        GameComponentHandle GenerateRenderComponent(GameEntityHandle owner, unsigned int model_handle);
        GameComponentHandle GeneratePointLightComponent(GameEntityHandle owner);
        
        template <typename T>
        friend T& ResolveHandle(const ObjectManagerHandle<T>& handle);
        
        template <typename T, typename Handle>
        friend T& ResolveHandleAs(const ObjectManagerHandle<Handle>& handle);
        
    };
    
    template <>
    inline GameComponent& ResolveHandle<GameComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        unsigned int index = handle.index();
        
        switch (handle.type()) {
            case BODY_COMPONENT:
                return GameComponentManager::instance_.body_components_.GetObject(index);
            case CONTROL_COMPONENT:
                return GameComponentManager::instance_.control_components_.GetObject(index);
            case AI_COMPONENT:
                return GameComponentManager::instance_.ai_components_.GetObject(index);
            case RENDER_COMPONENT:
                return GameComponentManager::instance_.render_components_.GetObject(index);
            case POINT_LIGHT_COMPONENT:
                return GameComponentManager::instance_.point_light_components_.GetObject(index);
            default:
                throw ObjectManagerHandleException();
        }
    }
    
    template <>
    inline AiComponent& ResolveHandle<AiComponent>(const ObjectManagerHandle<AiComponent>& handle)
    {
        if (handle.type() == AI_COMPONENT) {
            return GameComponentManager::instance_.ai_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline BodyComponent& ResolveHandleAs<BodyComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == BODY_COMPONENT) {
            return GameComponentManager::instance_.body_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline ControlComponent& ResolveHandleAs<ControlComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == CONTROL_COMPONENT) {
            return GameComponentManager::instance_.control_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline AiComponent& ResolveHandleAs<AiComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == AI_COMPONENT) {
            return GameComponentManager::instance_.ai_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline RenderComponent& ResolveHandleAs<RenderComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == RENDER_COMPONENT) {
            return GameComponentManager::instance_.render_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }
    
    template <>
    inline PointLightComponent& ResolveHandleAs<PointLightComponent>(const ObjectManagerHandle<GameComponent>& handle)
    {
        if (handle.type() == POINT_LIGHT_COMPONENT) {
            return GameComponentManager::instance_.point_light_components_.GetObject(handle.index());
        }
        
        throw ObjectManagerHandleException();
    }

}

#endif // BOUNCE_ENGINE_GAME_COMPONENT_MANAGER_H_
