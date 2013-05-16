/*
 * App.h
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#ifndef APP_H_
#define APP_H_

#include "bounceGL.h"
#include "Event.h"
#include "Window.h"


namespace bounce {

class App {
private:
	bool running;
	GLuint programId;
	const EventManager& eventManager;

	void (*flush)(void*);
	void* context;
public:
	App(const EventManager& eventManager, void (*flush)(void*), void* context) :
		running(true), programId(0), eventManager(eventManager), context(context)  {
				this->flush = flush;
		}
	virtual ~App();

	int onExecute();

	bool onInit();
	void onEvent(Event* event);
	void onLoop();
	void onRender();
	void onCleanup();

	void onFlush();
};

} /* namespace bounce */
#endif /* APP_H_ */
