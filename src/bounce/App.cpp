/*
 * App.cpp
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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

GLuint matrixId;

GLfloat* colorBufferData;

GLfloat* createColorData() {
	//std::cout << "Create color data";


	GLfloat* colorDataArray = new GLfloat[12 * 3 * 3];

	int count = 18;

	for (int i = 0; i < 6 * count; i++) {

		GLfloat val = ((float) rand() / (RAND_MAX));
		for (int j = 0; j < count; j++) {
			colorDataArray[i * count + j] = val;
		}

		//colorDataArray[i * count + 0] = val;
		//colorDataArray[i * count + 1] = val;
		//colorDataArray[i * count + 2] = val;
		//colorDataArray[i * count + 3] = val;
		//colorDataArray[i * count + 4] = val;
		//colorDataArray[i * count + 5] = val;
		//colorDataArray[i] = 1.0f;
	}

	return colorDataArray;
};

bool App::onInit() {
	srand(time(0));

	colorBufferData = createColorData();
//	for (int i = 0; i < 12 * 3 * 3; i++) {
//		std::cout << colorBufferData[i] << std::endl;
//	}
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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1.0);

	GLuint vertexArrayId;
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);

	ShaderManager shaderManager;

	programId = shaderManager.loadShaders("shaders/triangleShader.vert.glsl",
			"shaders/triangleShader.frag.glsl");

	matrixId = glGetUniformLocation(programId, "mvp");
	return true;
}

void App::onEvent(Event* event) {
	if (event->type == Event::EventType::Quit) {
		running = false;
	}
}

void App::onLoop() {

}

static const GLfloat vertexBufferData[] = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
};



void App::onRender() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programId);


	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mvp = projection * view * model;

	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
			GL_STATIC_DRAW);



	//for (int i = 0; i < 12 * 3 * 3; i++) {
	//	std::cout << colorBufferData[i] << std::endl;
	//}

	//throw "error";



	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12 * 3 * 3, colorBufferData,
			GL_STATIC_DRAW);

	//delete colorBufferData;

	const int vertexArray = 0;
    const int colorArray = 1;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexArray, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(colorArray, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(colorArray);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

	glDisableVertexAttribArray(vertexArray);
	glDisableVertexAttribArray(colorArray);


	//delete colorBufferData;
//	model = glm::scale(2.5f, 1.5f, 1.5f);
//	mvp = projection * view * model;
//
//	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData2), vertexBufferData2,
//			GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 4);
//	glDisableVertexAttribArray(0);

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
