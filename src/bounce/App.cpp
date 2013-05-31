/*
 * App.cpp
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#include <cstdlib>
#include <ctime>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "App.h"
#include "ShaderManager.h"

#include "LockFreeQueue.h"
#include "log.h"
#include "DefaultLogger.h"

namespace bounce {

const float PI = 3.14159265358979f;
const float PI2 = PI * 2.0f;

static const GLfloat vertexBufferData[] = { -1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		1.0f,

		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		1.0f,

		1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		1.0f,

		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		1.0f,

		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
		1.0f,

		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		1.0f,

		-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f };

//App::App(const EventManager& eventManager) {
//	running = true;
//	this->eventManager = eventManager;
//}

App::~App() {
	//delete window;
}

GLuint matrixId;
GLfloat* colorBufferData;

glm::vec3 position = glm::vec3(0, 0, 15);
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.5f;

int xpos, ypos;

GLfloat* createColorData() {
	//std::cout << "Create color data";
	GLfloat* colorDataArray = new GLfloat[12 * 3 * 3];

	int sides = 6;
	int verticesPerSide = 6;
	int colorsPerVertex = 3;
	int colorsPerSide = verticesPerSide * colorsPerVertex;

	for (int i = 0; i < sides; i++) {
		GLfloat val = 0.5f; //((float) rand() / (RAND_MAX));

		for (int j = 0; j < verticesPerSide; j++) {
			int index = i * colorsPerSide + j * colorsPerVertex;
			if (i == 1) {
				colorDataArray[index] = 1.0f;
				colorDataArray[index + 1] = 1.0f;
			}
			if (i % 2 == 0) {
				colorDataArray[index] = 1.0f;
			}
			if (i % 3 == 0) {
				colorDataArray[index + 1] = 1.0f;
			}
			if (i % 4 == 0 || i % 5 == 0) {
				colorDataArray[index + 2] = 1.0f;
			}

//			else {
//				colorDataArray[index] = val;
//				colorDataArray[index + 1] = val;
//				colorDataArray[index + 2] = val;
//			}

//			std::cout << "i: " << i << " j: " << j << std::endl;
//			std::cout << index << " ";
//			std::cout << index + 1 << " ";
//			std::cout << index + 2 << " ";
//			std::cout << std::endl << std::endl;

		}
	}

//	for (int i = 0; i < 108; i++) {
//		std::cout << colorDataArray[i] << std::endl;
//	}

	return colorDataArray;
}
;



bool App::onInit() {
	Logger* logger = new DefaultLogger();
	LogManager::getInstance().setLogger(logger);

	srand(time(0));

	colorBufferData = createColorData();

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

int App::onExecute() {
	if (onInit() == false) {
		return -1;
	}

	LOG(LogLevel::Debug) << "testing" << std::flush;

	Event* event = 0;

	while (running) {
		event = eventManager.pollEvent();

		if (event != nullptr) {
			std::cout << event << std::endl;
		}

		while (event != nullptr) {
			onEvent(event);
			event = eventManager.pollEvent();
		}

		onLoop();
		onRender();
	}

	onCleanup();

	return 0;
}

void App::onEvent(Event* event) {
	if (event->getType() == EventType::Quit) {
		running = false;
	}

	if (event->getType() == EventType::Keydown) {
		KeydownEvent* keydownEvent = static_cast<KeydownEvent*>(event);

		Key key = keydownEvent->getKeysym().sym;

		if (key == Key::A) {
			horizontalAngle -= mouseSpeed;
		} else if (key == Key::D) {
			horizontalAngle += mouseSpeed;
		} else if (key == Key::W) {
			verticalAngle -= mouseSpeed;
		} else if (key == Key::S) {
			verticalAngle += mouseSpeed;
		}

		if (verticalAngle > PI2) {
			verticalAngle -= PI2;
		} else if (verticalAngle < 0.0f) {
			verticalAngle += PI2;
		}

		if (horizontalAngle > PI2) {
			horizontalAngle -= PI2;
		} else if (horizontalAngle < 0.0f) {
			horizontalAngle += PI2;
		}

		std::cout << "horiz: " << horizontalAngle << " vert: " << verticalAngle
				<< std::endl;
	}
}

void App::onLoop() {

}

void App::onRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programId);

	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));

	glm::vec3 position(4, 3, 3);
	float fov = initialFoV;

	glm::mat4 projection = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(position, glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), horizontalAngle,
			glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), verticalAngle, glm::vec3(1, 0, 0));

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

	onFlush();
}

void App::onCleanup() {
	//SDL_Quit();
}

void App::onFlush() {
	flush(context);
}

} /* namespace bounce */
