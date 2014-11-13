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

#include "app.h"

#include "importer/importer.h"
#include "renderer/model.h"

#include "bounce/game_entity.h"

#include "bounce/render_component.h"
#include "bounce/control_component.h"
#include "bounce/movement_component.h"


//#include "lock_free_queue.h"


namespace bounce {
    
    App::App(ApplicationContext& application_context) :
        running_(true), application_context_(application_context), event_manager_(application_context.event_manager()),
        texture_manager_(application_context_.root_path() + "/textures"),
        renderer_(
                  application_context_.root_path() + "/shaders/geometry_pass.vert.glsl",
                  application_context_.root_path() + "/shaders/geometry_pass.frag.glsl",
//                  application_context_.root_path() + "/shaders/triangleShader.vert.glsl",
//                  application_context_.root_path() + "/shaders/triangleShader.frag.glsl",
                  model_manager_, texture_manager_, material_manager_, vertex_buffer_),
        render_system_(application_context_, world_manager_, renderer_)
    {
        
    }

    App::~App() {
        //delete window;
    }

    bool App::onInit()
    {
        srand(time(0));

        Importer importer(model_manager_, texture_manager_, material_manager_, vertex_buffer_);

        
        unsigned int model_handle = importer.ImportFile(application_context_.root_path() + "/models/simple_craft.dae");

        render_system_.startup();
//        renderer_.LoadVertexShader(application_context_.root_path() + "/triangleShader.vert.glsl");
//        renderer_.LoadFragmentShader(application_context_.root_path() + "/triangleShader.frag.glsl");
//        renderer_.LinkProgram();
        
        
        GameEntity* cube = new GameEntity();
        RenderComponent* render_component = new RenderComponent(&render_system_, model_handle);
        cube->AttachComponent(render_component);
        
        render_component->Startup();
        
        ControlComponent* control_component = new ControlComponent(keyboard_state_);
        cube->AttachComponent(control_component);
        
        MovementComponent* movement_component = new MovementComponent(timer_);
        cube->AttachComponent(movement_component);
        
        world_manager_.AddEntity(cube);

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

        while (running_) {
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

            application_context_.Update();
            
            while ((event = event_manager_.PollEvent()) != nullptr) {
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

        EventType event_type = event.type();

        if (event_type == EVENT_QUIT) {
            running_ = false;
        }

        if (event_type == EVENT_KEYDOWN || event_type == EVENT_KEYUP) {

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
        application_context_.Flush();
    }

} /* namespace bounce */
