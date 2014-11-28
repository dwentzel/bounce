#include "app.h"

#include "logging/log.h"

#include "framework/object_cache.h"

#include "importer/importer.h"

#include "bounce/game_entity.h"

#include "bounce/object_manager.h"
#include "bounce/body_component.h"
#include "bounce/render_component.h"
#include "bounce/point_light_component.h"

#include "bounce/control_component.h"
#include "bounce/position_component.h"

namespace bounce {
    
    App::App(ApplicationContext& application_context) :
    running_(true), application_context_(application_context), event_manager_(application_context.event_manager()),
    resource_loader_(application_context_.root_path()),
    texture_manager_(application_context_.root_path() + "/textures"),
    renderer_(resource_loader_, light_manager_, model_manager_, texture_manager_, material_manager_, vertex_buffer_),
    object_manager_(ObjectManager::instance_),
    input_system_(keyboard_state_, object_manager_.control_components()),
    movement_system_(object_manager_.body_components()),
    render_system_(application_context_, object_manager_.render_components(), object_manager_.point_light_components(), renderer_)
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
        
        GameComponentHandle light0_point_light_component_handle = object_manager_.GeneratePointLightComponent(light0_handle);
        PointLightComponent& light0_point_light_component = ResolveHandleAs<PointLightComponent>(light0_point_light_component_handle);
        light0_point_light_component.diffuse_intensity(4.0f);
        light0_point_light_component.exp_attenuation(0.3f);
        light0_point_light_component.color(glm::vec3(0.0f, 1.0f, 0.0f));
        
        light0.AttachComponent(light0_point_light_component_handle);
        light0_point_light_component.Startup();
        
        GameComponentHandle light0_body_component_handle = object_manager_.GenerateBodyComponent(light0_handle);
        BodyComponent& light0_body_component = ResolveHandleAs<BodyComponent>(light0_body_component_handle);
        light0_body_component.position(glm::vec3(0.0f, 0.5f, 0.5f));
        light0.AttachComponent(light0_body_component_handle);
        light0_body_component.Startup();
        
        
        GameEntityHandle light1_handle = object_manager_.GenerateGameEntity();
        GameEntity& light1 = ResolveHandle(light1_handle);
        
        GameComponentHandle light1_point_light_component_handle = object_manager_.GeneratePointLightComponent(light1_handle);
        PointLightComponent& light1_point_light_component = ResolveHandleAs<PointLightComponent>(light1_point_light_component_handle);
        light1_point_light_component.diffuse_intensity(4.0f);
        light1_point_light_component.exp_attenuation(0.3f);
        light1_point_light_component.color(glm::vec3(1.0f, 0.0f, 0.0f));
        
        light1.AttachComponent(light1_point_light_component_handle);
        light1_point_light_component.Startup();
        
        GameComponentHandle light1_body_component_handle = object_manager_.GenerateBodyComponent(light1_handle);
        BodyComponent& light1_body_component = ResolveHandleAs<BodyComponent>(light1_body_component_handle);
        light1_body_component.position(glm::vec3(0.0f, -0.5f, 0.5f));
        light1.AttachComponent(light1_body_component_handle);
        light1_body_component.Startup();
        
        
        GameEntityHandle light2_handle = object_manager_.GenerateGameEntity();
        GameEntity& light2 = ResolveHandle(light2_handle);
        
        GameComponentHandle light2_point_light_component_handle = object_manager_.GeneratePointLightComponent(light2_handle);
        PointLightComponent& light2_point_light_component = ResolveHandleAs<PointLightComponent>(light2_point_light_component_handle);
        light2_point_light_component.diffuse_intensity(4.0f);
        light2_point_light_component.exp_attenuation(0.3f);
        light2_point_light_component.color(glm::vec3(0.0f, 0.0f, 1.0f));
        
        light2.AttachComponent(light2_point_light_component_handle);
        light2_point_light_component.Startup();
        
        GameComponentHandle light2_body_component_handle = object_manager_.GenerateBodyComponent(light2_handle);
        BodyComponent& light2_body_component = ResolveHandleAs<BodyComponent>(light2_body_component_handle);
        light2_body_component.position(glm::vec3(0.5f, 0.0f, 0.5f));
        light2.AttachComponent(light2_body_component_handle);
        light2_body_component.Startup();
        
        
        GameEntityHandle ship_handle = object_manager_.GenerateGameEntity();
        GameEntity& ship = ResolveHandle(ship_handle);
        
        GameComponentHandle ship_body_component_handle = object_manager_.GenerateBodyComponent(ship_handle);
        BodyComponent& ship_body_component = ship_body_component_handle.ResolveAs<BodyComponent>();
        ship_body_component.max_speed(0.1f);
        ship_body_component.rotation_acceleration(0.0001f);
        
        ship.AttachComponent(ship_body_component_handle);
        ship_body_component.Startup();
        
        GameComponentHandle render_component_handle = object_manager_.GenerateRenderComponent(ship_handle, model_handle);
        RenderComponent& render_component = ResolveHandleAs<RenderComponent>(render_component_handle);
        ship.AttachComponent(render_component_handle);
        render_component.Startup();
        
        GameComponentHandle control_component_handle = object_manager_.GenerateControlComponent(ship_handle, keyboard_state_);
        ControlComponent& control_component = control_component_handle.ResolveAs<ControlComponent>();
        ship.AttachComponent(control_component_handle);
        control_component.Startup();
        
        
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
        
        EventPtr event = 0;
        
        timer_.Start();
        float frame_time;
        float slice_time = 0.0f;
        float delta_time = 10.0f;
        int frame_count = 0;
        float accumulated_time = 0.0f;
        
        while (running_) {
            timer_.SetFrameTime();
            timer_.Reset();
            frame_time = timer_.frame_time();
            slice_time += frame_time;
            
            while (slice_time > delta_time) {
                slice_time -= delta_time;
                
//                LOG_DEBUG << "slice time " << slice_time;
                
                application_context_.Update();
                
                while ((event = event_manager_.PollEvent()) != nullptr) {
                    onEvent(*event);
                }
                
                input_system_.Update(delta_time);
                movement_system_.Update(delta_time);
                
            }
            
//            LOG_DEBUG << "frame time " << frame_time;
            accumulated_time += frame_time;
            ++frame_count;
            
            if (accumulated_time > 1000.0f) {
                float fps = frame_count * 1000.0f / accumulated_time;
                LOG_DEBUG << "fps: " << fps << std::endl;
                frame_count = 0;
                accumulated_time = 0.0f;
            }
            
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
