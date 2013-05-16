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

public:
	App(const EventManager& eventManager) :
		programId(0), eventManager(eventManager) {}
	virtual ~App();

	int onExecute();

	bool onInit();
	void onEvent(Event* event);
	void onLoop();
	void onRender();
	void onCleanup();
};

} /* namespace bounce */
#endif /* APP_H_ */
