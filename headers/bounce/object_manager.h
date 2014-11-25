#ifndef BOUNCE_BOUNCE_OBJECT_MANAGER_
#define BOUNCE_BOUNCE_OBJECT_MANAGER_

#include "framework/object_cache.h"
#include "game_entity.h"
#include "render_component.h"
#include "body_component.h"

namespace bounce {

    class ObjectManager {
    private:
        ObjectCache<GameEntity> game_entities_;
        ObjectCache<RenderComponent> render_components_;
        ObjectCache<BodyComponent> body_components_;
        
    public:

        const ObjectCache<GameEntity>& game_entities() const;
        const ObjectCache<RenderComponent>& render_components() const;

        BodyComponentCache& body_components();
        const BodyComponentCache& body_components() const;
        
        unsigned int GenerateGameEntity();
        unsigned int GenerateRenderComponent(unsigned int model_handle);
        unsigned int GenerateBodyComponent();
        
        GameEntity& GetGameEntity(unsigned int handle);
        RenderComponent& GetRenderComponent(unsigned int handle);
        BodyComponent& GetBodyComponent(unsigned int handle);
        
    };

    inline const ObjectCache<GameEntity>& ObjectManager::game_entities() const
    {
        return game_entities_;
    }
    
    inline const ObjectCache<RenderComponent>& ObjectManager::render_components() const
    {
        return render_components_;
    }
    
    inline BodyComponentCache& ObjectManager::body_components()
    {
        return body_components_;
    }
    
    inline const BodyComponentCache& ObjectManager::body_components() const
    {
        return body_components_;
    }
    
    inline unsigned int ObjectManager::GenerateGameEntity()
    {
        unsigned int handle = game_entities_.GenerateObject();
        return handle;
    }
    
    inline unsigned int ObjectManager::GenerateRenderComponent(unsigned int model_handle)
    {
        unsigned int handle = render_components_.GenerateObject(model_handle);
        return handle;
    }
    
    inline unsigned int ObjectManager::GenerateBodyComponent()
    {
        unsigned int handle = body_components_.GenerateObject();
        return handle;
    }
    
    inline GameEntity& ObjectManager::GetGameEntity(unsigned int handle)
    {
        return game_entities_.GetObject(handle);
    }
    
    inline RenderComponent& ObjectManager::GetRenderComponent(unsigned int handle)
    {
        return render_components_.GetObject(handle);
    }
    
    inline BodyComponent& ObjectManager::GetBodyComponent(unsigned int handle)
    {
        return body_components_.GetObject(handle);
    }
}

#endif // BOUNCE_BOUNCE_OBJECT_MANAGER_
