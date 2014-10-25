#ifndef BOUNCE_RENDER_SYSTEM_H
#define BOUNCE_RENDER_SYSTEM_H

#include "bounce_gl.h"
#include "game_system.h"
#include "application_context.h"
#include "world_manager.h"

namespace bounce {
    
    class RenderSystem : public GameSystem {
    private:
        GLuint program_id_;
        GLuint matrix_id_;
        
        const ApplicationContext& application_context_;
        const WorldManager& world_manager_;
        
    public:
        RenderSystem(const ApplicationContext& application_context, const WorldManager& world_manager) : application_context_(application_context), world_manager_(world_manager) {
            
        }
        
        virtual void startup();
        virtual void shutdown();
        virtual void update();
    };
    
}

#endif