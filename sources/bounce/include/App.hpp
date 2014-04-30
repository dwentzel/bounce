/*
 * App.h
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#ifndef APP_H_
#define APP_H_

#include <memory>

#include "bounceGL.hpp"
#include "Event.hpp"
#include "Timer.hpp"
#include "KeyboardState.hpp"

namespace bounce {

class App {
private:
	bool running;
	GLuint programId;
	EventManager& eventManager;
	KeyboardState keyboardState;

	void (*flush)(void*);
	void* context;
	Timer timer;

public:
	App(EventManager& eventManager, void (*flush)(void*), void* context) :
		running(true), programId(0), eventManager(eventManager), context(context)  {
		this->flush = flush;
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
