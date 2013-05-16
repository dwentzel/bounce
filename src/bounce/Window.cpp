/*
 * Window.cpp
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#include "Window.h"

namespace bounce {

Window::Window() {
	// TODO Auto-generated constructor stub

}

Window::~Window() {
	// TODO Auto-generated destructor stub
}

SDLWindow::SDLWindow() {

}

SDLWindow::~SDLWindow() {

}

void SDLWindow::init(const WindowProperties& properties) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw WindowException();
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	if ((surface = SDL_SetVideoMode(properties.width, properties.height, 32,
			SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == 0) {
		throw WindowException();
	}
}

CocoaWindow::CocoaWindow() {

}

CocoaWindow::~CocoaWindow() {

}

void CocoaWindow::init(const WindowProperties& properties) {

}

} /* namespace bounce */
