#ifndef BOUNCE_APP_H_
#define BOUNCE_APP_H_

#include <memory>

#include "framework/object_cache.h"
#include "framework/timer.h"
#include "framework/resource_loader.h"

#include "renderer/vertex_buffer.h"
#include "renderer/light_manager.h"
#include "renderer/model_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/material_manager.h"
#include "renderer/opengl_renderer.h"

#include "bounce/application_context.h"
#include "bounce/event.h"
#include "bounce/keyboard_state.h"
#include "bounce/input_system.h"
#include "bounce/movement_system.h"
#include "bounce/render_system.h"

#include "bounce/object_manager.h"

#include "bounce/render_component.h"


namespace bounce {
    
    class App {
    private:
        bool running_;
        
        ApplicationContext& application_context_;
        EventManager& event_manager_;
        
        ResourceLoader resource_loader_;
        
        VertexBuffer vertex_buffer_;
        LightManager light_manager_;
        ModelManager model_manager_;
        TextureManager texture_manager_;
        MaterialManager material_manager_;
        
        OpenGLRenderer renderer_;
        
        KeyboardState keyboard_state_;
        
        Timer timer_;
        
        ObjectManager& object_manager_;
        
        InputSystem input_system_;
        MovementSystem movement_system_;
        RenderSystem render_system_;
        
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        
    public:
        App(ApplicationContext& application_context);
        
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
