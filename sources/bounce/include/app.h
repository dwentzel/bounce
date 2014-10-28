/*
 * App.h
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_APP_H_
#define BOUNCE_APP_H_

#include <memory>

#include "application_context.h"
#include "bounce_gl.h"
#include "event.h"
#include "timer.h"
#include "keyboard_state.h"
#include "object.h"
#include "render_system.h"
#include "vertex_buffer.h"
#include "world_manager.h"

namespace bounce {

class App {
private:
    bool running;

    const ApplicationContext& application_context_;
    const EventManager& event_manager_;
   
    VertexBuffer vertex_buffer_;
    
    KeyboardState keyboard_state_;

    Timer timer_;
    
    WorldManager world_manager_;

    RenderSystem render_system_;
    
public:
	App(const ApplicationContext& application_context) :
		running(true), application_context_(application_context), event_manager_(application_context.event_manager()),
        render_system_(application_context_, world_manager_, vertex_buffer_)
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
