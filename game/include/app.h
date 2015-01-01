#ifndef BOUNCE_APP_H_
#define BOUNCE_APP_H_

#include <memory>

#include "framework/timer.h"
#include "framework/resource_loader.h"

#include "renderer/vertex_buffer.h"
#include "renderer/model_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/material_manager.h"
#include "renderer/opengl_renderer.h"

#include "engine/application_context.h"
#include "engine/event.h"
#include "engine/keyboard_state.h"
#include "engine/input_system.h"
#include "engine/movement_system.h"
#include "engine/render_system.h"
#include "engine/game_entity_manager.h"
#include "engine/game_component_manager.h"

namespace bounce {
    
    class App {
    private:
        bool running_;
        
        ApplicationContext& application_context_;
        EventManager& event_manager_;
        
        WindowContext& window_context_;
        
        ResourceLoader resource_loader_;
        
        VertexBuffer vertex_buffer_;
        ModelManager model_manager_;
        TextureManager texture_manager_;
        MaterialManager material_manager_;
        
        OpenGLRenderer renderer_;
        
        KeyboardState keyboard_state_;
        
        Timer timer_;
        
        GameEntityManager entity_manager_;
        GameComponentManager component_manager_;
        
        InputSystem input_system_;
        MovementSystem movement_system_;
        RenderSystem render_system_;
        
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        
    public:
        App(ApplicationContext& application_context, WindowContext& window_context);
        
        ~App();
        
        int onExecute();
        
        bool onInit();
        void onEvent(const Event& event);
        void onLoop();
        void onRender();
        void onCleanup();
        
        void onFlush();
    };
    
}

#endif // BOUNCE_APP_H_
