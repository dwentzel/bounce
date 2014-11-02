/*
 * App.cpp
 *
 *  Created on: 12 maj 2013
 *      Author: daniel
 */

#include <cstdlib>
#include <ctime>

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "logging/log.h"
#include "logging/default_logger.h"

#include "app.h"
#include "shader_manager.h"
#include "game_entity.h"

#include "render_component.h"
#include "control_component.h"
#include "movement_component.h"

#include "importer/importer.h"
#include "renderer/model.h"

//#include "lock_free_queue.h"


namespace bounce {

    App::~App() {
        //delete window;
    }

    GLuint matrixId;

//    glm::vec3 position = glm::vec3(0, 0, 15);
//    float horizontalAngle = 0.0f;
//    float verticalAngle = 0.0f;
//    float initialFoV = 45.0f;
//    float speed = 3.0f;
//    float mouseSpeed = 0.5f;
//
//    int xpos, ypos;

    
    Model model;

    bool App::onInit()
    {
        srand(time(0));

        Importer importer(material_manager_, vertex_buffer_);
        
        model = importer.ImportFile("models/simple_craft.dae");

        render_system_.startup();
        
        GameEntity* cube = new GameEntity();
        //Mesh* cube_mesh = new Mesh();
        RenderComponent* render_component = new RenderComponent(&render_system_, &model);
        cube->AttachComponent(render_component);
        
//        ControlComponent* control_component = new ControlComponent(keyboard_state_, timer_);
        ControlComponent* control_component = new ControlComponent(keyboard_state_);
        cube->AttachComponent(control_component);
        
        MovementComponent* movement_component = new MovementComponent(timer_);
//        MovementComponent* movement_component = new MovementComponent();
        cube->AttachComponent(movement_component);
        
        world_manager_.AddEntity(cube);
//
        
        
        return true;
    }

    int App::onExecute() {
        if (onInit() == false) {
            return -1;
        }

        LOG_DEBUG << "testing";

        EventPtr event = 0;

        timer_.Start();
        float delta_time;
        int frame_count = 0;
        float accumulated_time = 0.0f;

        while (running) {
            timer_.SetFrameTime();
            timer_.Reset();
            delta_time = timer_.frame_time();

            accumulated_time += delta_time;
            ++frame_count;

            if (accumulated_time > 1000.0f) {
                float fps = frame_count * 1000.0f / accumulated_time;
                LOG_DEBUG << "fps: " << fps << std::endl;
                frame_count = 0;
                accumulated_time = 0.0f;
            }

//            LOG(LogLevel::Debug) << deltaTime << "\n";

            while ((event = event_manager_.pollEvent()) != nullptr) {
                onEvent(*event);
            }

//            onLoop();
//            onRender();
            
            const GameEntityList& entities = world_manager_.entities();
            
            for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
                GameEntity* entity = *i;
                
                entity->UpdateComponentOfType(MOVEMENT_COMPONENT);
            }
            
            render_system_.update();
        }

        onCleanup();

        return 0;
    }

    void App::onEvent(const Event& event) {

        EventType event_type = event.getType();

        if (event_type == EventType::Quit) {
            running = false;
        }

        if (event_type == EventType::Keydown || event_type == EventType::Keyup) {

            KeyboardEvent keyboard_event = static_cast<const KeyboardEvent&>(event);
            keyboard_state_.ProcessEvent(keyboard_event);

            const GameEntityList& entities = world_manager_.entities();
            
            for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
                GameEntity* entity = *i;
                
                entity->UpdateComponentOfType(CONTROL_COMPONENT);
            }
        }
    }

    void App::onLoop() {

    }

    void App::onRender()
    {

    }

    void App::onCleanup() {
        //SDL_Quit();
    }

    void App::onFlush() {
        application_context_.flush();
    }

} /* namespace bounce */
