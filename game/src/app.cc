#include "app.h"

#include "logging/log.h"

#include "framework/object_cache.h"

#include "importer/importer.h"

#include "bounce/game_entity.h"

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
        GameEntity& light0 = light0_handle.ResolveAs<GameEntity>();
        
        GameComponentHandle light0_point_light_component_handle = object_manager_.GeneratePointLightComponent();
        PointLightComponent& light0_point_light_component = light0_point_light_component_handle.ResolveAs<PointLightComponent>();
        light0_point_light_component.diffuse_intensity(4.0f);
        light0_point_light_component.exp_attenuation(0.3f);
        light0_point_light_component.color(glm::vec3(0.0f, 1.0f, 0.0f));
        
        light0.AttachComponent(light0_point_light_component_handle);
        light0_point_light_component.Startup();
        
        GameComponentHandle light0_body_component_handle = object_manager_.GenerateBodyComponent();
        BodyComponent& light0_body_component = light0_body_component_handle.ResolveAs<BodyComponent>();
        light0_body_component.position(glm::vec3(0.0f, 0.5f, 0.5f));
        light0.AttachComponent(light0_body_component_handle);
        light0_body_component.Startup();
        
        
        GameEntityHandle light1_handle = object_manager_.GenerateGameEntity();
        GameEntity& light1 = light1_handle.ResolveAs<GameEntity>();
        
        GameComponentHandle light1_point_light_component_handle = object_manager_.GeneratePointLightComponent();
        PointLightComponent& light1_point_light_component = light1_point_light_component_handle.ResolveAs<PointLightComponent>();
        light1_point_light_component.diffuse_intensity(4.0f);
        light1_point_light_component.exp_attenuation(0.3f);
        light1_point_light_component.color(glm::vec3(1.0f, 0.0f, 0.0f));
        
        light1.AttachComponent(light1_point_light_component_handle);
        light1_point_light_component.Startup();
        
        GameComponentHandle light1_body_component_handle = object_manager_.GenerateBodyComponent();
        BodyComponent& light1_body_component = light1_body_component_handle.ResolveAs<BodyComponent>();
        light1_body_component.position(glm::vec3(0.0f, -0.5f, 0.5f));
        light1.AttachComponent(light1_body_component_handle);
        light1_body_component.Startup();
        
        
        GameEntityHandle light2_handle = object_manager_.GenerateGameEntity();
        GameEntity& light2 = light2_handle.ResolveAs<GameEntity>();
        
        GameComponentHandle light2_point_light_component_handle = object_manager_.GeneratePointLightComponent();
        PointLightComponent& light2_point_light_component = light2_point_light_component_handle.ResolveAs<PointLightComponent>();
        light2_point_light_component.diffuse_intensity(4.0f);
        light2_point_light_component.exp_attenuation(0.3f);
        light2_point_light_component.color(glm::vec3(0.0f, 0.0f, 1.0f));
        
        light2.AttachComponent(light2_point_light_component_handle);
        light2_point_light_component.Startup();
        
        GameComponentHandle light2_body_component_handle = object_manager_.GenerateBodyComponent();
        BodyComponent& light2_body_component = light2_body_component_handle.ResolveAs<BodyComponent>();
        light2_body_component.position(glm::vec3(0.5f, 0.0f, 0.5f));
        light2.AttachComponent(light2_body_component_handle);
        light2_body_component.Startup();

        
        GameEntityHandle ship_handle = object_manager_.GenerateGameEntity();
        GameEntity& ship = ship_handle.ResolveAs<GameEntity>();
        
        GameComponentHandle render_component_handle = object_manager_.GenerateRenderComponent(model_handle);
        RenderComponent& render_component = render_component_handle.ResolveAs<RenderComponent>();
        
        ship.AttachComponent(render_component_handle);
        
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
