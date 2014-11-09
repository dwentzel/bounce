/*
 * App.h
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_APP_H_
#define BOUNCE_APP_H_

#include <memory>

#include "framework/timer.h"

#include "renderer/vertex_buffer.h"
#include "renderer/model_manager.h"
#include "renderer/material_manager.h"
#include "renderer/opengl_renderer.h"

#include "bounce/application_context.h"
#include "bounce/event.h"
#include "bounce/keyboard_state.h"
#include "bounce/render_system.h"
#include "bounce/world_manager.h"


namespace bounce {

class App {
private:
    bool running_;

    ApplicationContext& application_context_;
    EventManager& event_manager_;
   
    VertexBuffer vertex_buffer_;
    ModelManager model_manager_;
    MaterialManager material_manager_;

    OpenGLRenderer renderer_;
    
    KeyboardState keyboard_state_;

    Timer timer_;
    
    WorldManager world_manager_;

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

} /* namespace bounce */
#endif /* APP_H_ */
