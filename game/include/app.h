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
	App(ApplicationContext& application_context) :
		running_(true), application_context_(application_context), event_manager_(application_context.event_manager()),
        renderer_(application_context_.root_path() + "/triangleShader.vert.glsl",
                  application_context_.root_path() + "/triangleShader.frag.glsl",
                  model_manager_, material_manager_, vertex_buffer_),
        render_system_(application_context_, world_manager_, renderer_)
    {
	
    }
	virtual ~App();

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
