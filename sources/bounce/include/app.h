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

namespace bounce {

class App {
private:
    bool running;
    GLuint programId;

    const ApplicationContext& application_context_;
    const EventManager& eventManager;
    KeyboardState keyboardState;

    Timer timer_;
    float delta_time_;

    Object object;

public:
	App(const ApplicationContext& application_context) :
		running(true), programId(0), application_context_(application_context), eventManager(application_context.event_manager()) {
	
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
