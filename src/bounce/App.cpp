/*
 * App.cpp
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#include "App.h"
#include "ShaderManager.h"

namespace bounce {

//App::App(const EventManager& eventManager) {
//	running = true;
//	this->eventManager = eventManager;
//}

App::~App() {
	//delete window;
}

int App::onExecute() {
	if (onInit() == false) {
		return -1;
	}

	Event* event = 0;

	while (running) {
		while ((event = eventManager.pollEvent()) != 0) {
			onEvent(event);
		}

		onLoop();
		onRender();
	}

	onCleanup();

	return 0;
}

bool App::onInit() {

	//WindowProperties properties;
	//properties.width = 640;
	//properties.height = 480;

	//window = new SDLWindow();
	//window->init(properties);

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return -1;
	}

	GLuint vertexArrayId;
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);

	ShaderManager shaderManager;

	programId = shaderManager.loadShaders("shaders/triangleShader.vert.glsl",
			"shaders/triangleShader.frag.glsl");


	return true;
}

void App::onEvent(Event* event) {
	if (event->type == Event::EventType::Quit) {
		running = false;
	}
}

void App::onLoop() {

}

static const GLfloat vertexBufferData[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f };

void App::onRender() {

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(programId);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
			GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	onFlush();
	//SDL_GL_SwapBuffers();
}

void App::onCleanup() {
	//SDL_Quit();
}

void App::onFlush() {
	flush(context);
}

} /* namespace bounce */
