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
#include "bounce/point_light_component.h"
#include "bounce/position_component.h"

#include "framework/object_cache.h"
#include "bounce/body_component.h"

namespace bounce {
    

    
    App::App(ApplicationContext& application_context) :
        running_(true), application_context_(application_context), event_manager_(application_context.event_manager()),
        resource_loader_(application_context_.root_path()),
        texture_manager_(application_context_.root_path() + "/textures"),
        renderer_(resource_loader_, light_manager_, model_manager_, texture_manager_, material_manager_, vertex_buffer_),
        movement_system_(object_manager_.body_components()),
        render_system_(application_context_, object_manager_.render_components(), renderer_)
    {
        
    }

    App::~App() {
        //delete window;
    }

    bool App::onInit()
    {
        srand(time(0));

        Importer importer(resource_loader_, model_manager_, texture_manager_, material_manager_, vertex_buffer_);
        unsigned int model_handle = importer.ImportFile("simple_craft.dae");
        
        render_system_.Startup();
        
        GameEntityHandle light0_handle = object_manager_.GenerateGameEntity();
        GameEntity& light0 = light0_handle.Resolve();
        
        GameComponentHandle light0_point_light_component_handle = object_manager_.GeneratePointLightComponent();
        PointLightComponent& point_light_component0 = light0_point_light_component_handle.ResolveAs<PointLightComponent>();
        point_light_component0.diffuse_intensity(4.0f);
        point_light_component0.exp_attenuation(0.3f);
        point_light_component0.color(glm::vec3(0.0f, 1.0f, 0.0f));
        
        light0.AttachComponent(point_light_component0);
        point_light_component0.Startup();
        
        GameComponentHandle light0_body_component_handle = object_manager_.GenerateBodyComponent();
        BodyComponent& light0_body_component = light0_body_component_handle.ResolveAs<BodyComponent>();
        light0_body_component.position(glm::vec3(0.0f, 0.5f, 0.5f));
        light0.AttachComponent(light0_body_component);
        light0_body_component.Startup();
//
//        PositionComponent* position_component0 = new PositionComponent(glm::vec3(0.0f, 0.5f, 0.5f));
//        light0.AttachComponent(position_component0);
//        position_component0->Startup();
//        
//        unsigned int light1_handle = object_manager_.GenerateGameEntity();
//        GameEntity& light1 = object_manager_.GetGameEntity(light1_handle);
//        
//        PointLightComponent* light_component1 =
//          new PointLightComponent(light_manager_, 0.0f, 5.0f, 0.0f, 0.0f, 0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
//
//        light1.AttachComponent(light_component1);
//        light_component1->Startup();
//        
//        PositionComponent* position_component1 = new PositionComponent(glm::vec3(0.0f, -0.5f, 0.5f));
//        light1.AttachComponent(position_component1);
//        position_component1->Startup();
//        
//        unsigned int light2_handle = object_manager_.GenerateGameEntity();
//        GameEntity& light2 = object_manager_.GetGameEntity(light2_handle);
//        
//        PointLightComponent* light_component2 =
//            new PointLightComponent(light_manager_, 0.0f, 0.7f, 0.0f, 0.0f, 0.3f, glm::vec3(0.0f, 0.0f, 1.0f));
//
//        light2.AttachComponent(light_component2);
//        light_component2->Startup();
//        
//        PositionComponent* position_component2 = new PositionComponent(glm::vec3(0.5f, 0.0f, 0.5f));
//        light2.AttachComponent(position_component2);
//        position_component2->Startup();
        
        GameEntityHandle ship_handle = object_manager_.GenerateGameEntity();
        GameEntity& ship = ship_handle.Resolve();
        
        GameComponentHandle render_component_handle = object_manager_.GenerateRenderComponent(model_handle);
        RenderComponent& render_component = render_component_handle.ResolveAs<RenderComponent>();
        
        ship.AttachComponent(render_component);
        
        render_component.Startup();
        
//        ControlComponent* control_component = new ControlComponent(keyboard_state_);
//        ship.AttachComponent(control_component);
        
        //MovementComponent* movement_component = new MovementComponent(timer_);
        //cube->AttachComponent(movement_component);

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
            
            movement_system_.Update(delta_time);
            render_system_.Update(delta_time);
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

//            const GameEntityList& entities = world_manager_.entities();
//            
//            for (GameEntityList::const_iterator i = entities.begin(); i != entities.end(); ++i) {
//                GameEntity* entity = *i;
//                
//                entity->UpdateComponentOfType(CONTROL_COMPONENT);
//            }
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
