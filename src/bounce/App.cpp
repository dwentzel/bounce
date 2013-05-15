/*
 * App.cpp
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#include "App.h"
#include "ShaderManager.h"



namespace bounce {

App::App() {
	running = true;
	surface = 0;
}

App::~App() {

}

int App::onExecute() {
	if (onInit() == false) {
		return -1;
	}

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		onLoop();
		onRender();
	}

	onCleanup();

	return 0;
}

bool App::onInit() {

	int width = 640;
	int height = 480;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
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

	if ((surface = SDL_SetVideoMode(width, height, 32,
			SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == 0) {
		return false;
	}

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

void App::onEvent(SDL_Event* event) {
	if (event->type == SDL_QUIT) {
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

	SDL_GL_SwapBuffers();
}

void App::onCleanup() {
	SDL_Quit();
}

} /* namespace bounce */
