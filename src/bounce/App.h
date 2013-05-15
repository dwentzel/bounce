/*
 * App.h
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#ifndef APP_H_
#define APP_H_

#include <SDL/SDL.h>
#include "bounceGL.h"


namespace bounce {

class App {
private:
	bool running;
	SDL_Surface* surface;
	GLuint programId;

public:
	App();
	virtual ~App();

	int onExecute();

	bool onInit();
	void onEvent(SDL_Event* event);
	void onLoop();
	void onRender();
	void onCleanup();
};

} /* namespace bounce */
#endif /* APP_H_ */
