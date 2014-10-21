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

#include "logging/log.h"
#include "logging/default_logger.h"

#include "app.h"
#include "shader_manager.h"

//#include "lock_free_queue.h"


namespace bounce {

    App::~App() {
        //delete window;
    }

    GLuint matrixId;

    glm::vec3 position = glm::vec3(0, 0, 15);
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;
    float speed = 3.0f;
    float mouseSpeed = 0.5f;

    int xpos, ypos;


    bool App::onInit()
    {
        srand(time(0));

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

        programId = shaderManager.loadShaders(
            "shaders/triangleShader.vert.glsl",
            "shaders/triangleShader.frag.glsl");

        matrixId = glGetUniformLocation(programId, "mvp");

        return true;
    }

    int App::onExecute() {
        if (onInit() == false) {
            return -1;
        }

        LOG_DEBUG << "testing";

        EventPtr event = 0;

        timer_.start();
        //float deltaTime;
        int frame_count = 0;
        float accumulated_time = 0.0f;

        while (running) {
            delta_time_ = timer_.getElapsedTime();
            accumulated_time += delta_time_;
            ++frame_count;

            if (accumulated_time > 1000.0f) {
                float fps = frame_count * 1000.0f / accumulated_time;
                //LOG(LogLevel::Debug) << "fps: " << fps << std::endl;
                frame_count = 0;
                accumulated_time = 0.0f;
            }

            //LOG(LogLevel::Debug) << deltaTime << "\n";

            while ((event = eventManager.pollEvent()) != nullptr) {
                onEvent(*event);
            }

            onLoop();
            onRender();
        }

        onCleanup();

        return 0;
    }

    void App::onEvent(const Event& event) {

        EventType eventType = event.getType();

        if (eventType == EventType::Quit) {
            running = false;
        }

        if (eventType == EventType::Keydown || eventType == EventType::Keyup) {

            KeyboardEvent keyboard_event = static_cast<const KeyboardEvent&>(event);
            keyboardState.processEvent(keyboard_event);

            Key key = keyboard_event.getKeysym().sym;

            int horizontal_acceleration = 0;
            int vertical_acceleration = 0;

            if (keyboardState.isDown(Key::A)) {
                --horizontal_acceleration;
            }

            if (keyboardState.isDown(Key::D)) {
                ++horizontal_acceleration;
            }

            if (keyboardState.isDown(Key::W)) {
                ++vertical_acceleration;
            }

            if (keyboardState.isDown(Key::S)) {
                --vertical_acceleration;
            }

            object.AccelerateHorizontal(horizontal_acceleration);
            object.AccelerateVertical(vertical_acceleration);

            //if (verticalAngle > PI2) {
            //    verticalAngle -= PI2;
            //}
            //else if (verticalAngle < 0.0f) {
            //    verticalAngle += PI2;
            //}

            //if (horizontalAngle > PI2) {
            //    horizontalAngle -= PI2;
            //}
            //else if (horizontalAngle < 0.0f) {
            //    horizontalAngle += PI2;
            //}

            //LOG_DEBUG << "horiz: " << horizontalAngle << " vert: " << verticalAngle
            //    << std::endl;
        }
    }

    void App::onLoop() {
        object.Animate(delta_time_);
    }

    void App::onRender() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);

        std::vector<GLfloat> vertices;

        GLfloat* object_vertex_array = object.vertex_data();
        int object_vertex_count = object.vertex_count();

        vertices.insert(vertices.end(), object_vertex_array, object_vertex_array + object_vertex_count);

        std::vector<GLfloat> normals;

        GLfloat* object_normal_data = object.normal_data();
        int object_normal_count = object.normal_count();

        normals.insert(normals.end(), object_normal_data, object_normal_data + object_normal_count);

        std::vector<GLfloat> colors;

        GLfloat* object_color_data = object.color_data();
        int object_color_count = object.color_count();

        colors.insert(colors.end(), object_color_data, object_color_data + object_color_count);

        std::vector<GLuint> indices;

        GLuint* object_index_data = object.index_data();
        int object_index_count = object.index_count();

        indices.insert(indices.end(), object_index_data, object_index_data + object_index_count);

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        GLuint normalBuffer;
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

        //GLuint element_buffer;
        //glGenBuffers(1, &element_buffer);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));

        glm::vec3 position(0, 0, 5);
        float fov = initialFoV;

        glm::mat4 projection = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(position, glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));

        //glm::mat4 model = glm::rotate(glm::mat4(1.0f), horizontalAngle,
        //    glm::vec3(0, 1, 0))
        //    * glm::rotate(glm::mat4(1.0f), verticalAngle, glm::vec3(1, 0, 0));

        glm::mat4 model = object.model_matrix();

        glm::mat4 mvp = projection * view * model;

        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        const int vertexArray = 0;
        const int colorArray = 1;
        const int normalArray = 2;

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(vertexArray, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(vertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(colorArray, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(colorArray);

        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(normalArray, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(normalArray);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

        glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

        glDisableVertexAttribArray(vertexArray);
        glDisableVertexAttribArray(colorArray);

        onFlush();
    }

    void App::onCleanup() {
        //SDL_Quit();
    }

    void App::onFlush() {
        application_context_.flush();
    }

} /* namespace bounce */
