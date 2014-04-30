/*
 * Window.h
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <exception>
#include <SDL/SDL.h>

namespace bounce {

class WindowException: public std::exception {

};

struct WindowProperties {
	int width;
	int height;
};

class Window {
public:
	Window();
	virtual ~Window();

	virtual void init(const WindowProperties& properties) = 0;
};

class SDLWindow: public Window {
private:
	SDL_Surface* surface;

public:
	SDLWindow();
	virtual ~SDLWindow();

	void init(const WindowProperties& properties);
};

class CocoaWindow: public Window {
	CocoaWindow();
	virtual ~CocoaWindow();

	void init(const WindowProperties& properties);
};

} /* namespace bounce */
#endif /* WINDOW_H_ */
