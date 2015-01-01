#include "app.h"

#include <ctime>

#include "logging/log.h"

#include "framework/object_cache.h"

#include "importer/importer.h"

#include "renderer/model_loader.h"

#include "engine/game_entity.h"

#include "engine/body_component.h"
#include "engine/render_component.h"
#include "engine/point_light_component.h"

#include "engine/control_component.h"
#include "engine/position_component.h"

#include "engine/ai_orbit_strategy.h"

namespace bounce {
    
    App::App(ApplicationContext& application_context, WindowContext& window_context)
    : running_(true),
      application_context_(application_context),
      event_manager_(application_context.event_manager()),
      window_context_(window_context),
      resource_loader_(application_context_.root_path()),
      texture_manager_(application_context_.root_path() + "/textures"),
      renderer_(resource_loader_, model_manager_, texture_manager_, material_manager_, vertex_buffer_),
      entity_manager_(),
      component_manager_(),
      input_system_(keyboard_state_, entity_manager_.game_entities(), component_manager_),
      movement_system_(entity_manager_.game_entities(), component_manager_),
      render_system_(application_context_, window_context_, entity_manager_.game_entities(), component_manager_, renderer_)
    {
        
    }
    
    App::~App() {
        //delete window;
    }
    
    bool App::onInit()
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        GameEntity::component_manager(&component_manager_);
        
        render_system_.Startup();        
        
        Importer importer(resource_loader_);
//        unsigned int model_handle = 0;// = importer.ImportFile("simple_craft.dae");
        
        ImportedModel imported_model = importer.LoadModel("simple_craft.dae");

        ModelLoader loader(texture_manager_, material_manager_, model_manager_);
        
        loader.Begin();
        
        unsigned int model_handle = loader.LoadModel(imported_model);
        
        loader.End();
        
        renderer_.BufferModelData(loader);
        
        
        GameEntityHandle light0_handle = entity_manager_.GenerateGameEntity();
        GameEntity& light0 = entity_manager_.ResolveHandle(light0_handle);
        
        GameComponentHandle light0_point_light_component_handle = component_manager_.GeneratePointLightComponent();
        PointLightComponent& light0_point_light_component = component_manager_.ResolveHandleAs<PointLightComponent>(light0_point_light_component_handle);
        light0_point_light_component.diffuse_intensity(4.0f);
        light0_point_light_component.exp_attenuation(0.3f);
        light0_point_light_component.color(glm::vec3(0.0f, 1.0f, 0.0f));
        
        light0.AttachComponent(light0_point_light_component_handle);
        light0_point_light_component.Startup();

        std::unique_ptr<AiStrategy> light0_ai_strategy(new AiOrbitStrategy(10.0f, 1, glm::vec3(0.0f, 0.5f, 0.0f)));
        GameComponentHandle light0_ai_component_handle = component_manager_.GenerateAiComponent(std::move(light0_ai_strategy));
        AiComponent& light0_ai_component = component_manager_.ResolveHandleAs<AiComponent>(light0_ai_component_handle);
        light0.AttachComponent(light0_ai_component_handle);
        light0_ai_component.Startup();
        GameComponentHandle light0_body_component_handle = component_manager_.GenerateBodyComponent();
        BodyComponent& light0_body_component = component_manager_.ResolveHandleAs<BodyComponent>(light0_body_component_handle);
        light0_body_component.position(glm::vec3(2.0f, 1.0f, 0.0f));
        light0.AttachComponent(light0_body_component_handle);
        light0_body_component.Startup();
        
        
        
        GameEntityHandle light1_handle = entity_manager_.GenerateGameEntity();
        GameEntity& light1 = entity_manager_.ResolveHandle(light1_handle);
        
        GameComponentHandle light1_point_light_component_handle = component_manager_.GeneratePointLightComponent();
        PointLightComponent& light1_point_light_component = component_manager_.ResolveHandleAs<PointLightComponent>(light1_point_light_component_handle);
        light1_point_light_component.diffuse_intensity(4.0f);
        light1_point_light_component.exp_attenuation(0.3f);
        light1_point_light_component.color(glm::vec3(1.0f, 0.0f, 0.0f));
        light1.AttachComponent(light1_point_light_component_handle);
        light1_point_light_component.Startup();
        
        std::unique_ptr<AiStrategy> light1_ai_strategy(new AiOrbitStrategy(10.0f, 1, glm::vec3(0.0f, 0.5f, 0.0f)));
        GameComponentHandle light1_ai_component_handle = component_manager_.GenerateAiComponent(std::move(light1_ai_strategy));
        AiComponent& light1_ai_component = component_manager_.ResolveHandleAs<AiComponent>(light1_ai_component_handle);
        light1.AttachComponent(light1_ai_component_handle);
        light1_ai_component.Startup();
        
        GameComponentHandle light1_body_component_handle = component_manager_.GenerateBodyComponent();
        BodyComponent& light1_body_component = component_manager_.ResolveHandleAs<BodyComponent>(light1_body_component_handle);
        light1_body_component.position(glm::vec3(0.0f, 0.5f, 2.0f));
        light1.AttachComponent(light1_body_component_handle);
        light1_body_component.Startup();

        
        GameEntityHandle light2_handle = entity_manager_.GenerateGameEntity();
        GameEntity& light2 = entity_manager_.ResolveHandle(light2_handle);
        
        GameComponentHandle light2_point_light_component_handle = component_manager_.GeneratePointLightComponent();
        PointLightComponent& light2_point_light_component = component_manager_.ResolveHandleAs<PointLightComponent>(light2_point_light_component_handle);
        light2_point_light_component.diffuse_intensity(4.0f);
        light2_point_light_component.exp_attenuation(0.3f);
        light2_point_light_component.color(glm::vec3(0.0f, 0.0f, 1.0f));
        light2.AttachComponent(light2_point_light_component_handle);
        light2_point_light_component.Startup();
        
        std::unique_ptr<AiStrategy> light2_ai_strategy(new AiOrbitStrategy(10.0f, 1, glm::vec3(0.0f, 0.5f, 0.0f)));
        GameComponentHandle light2_ai_component_handle = component_manager_.GenerateAiComponent(std::move(light2_ai_strategy));
        AiComponent& light2_ai_component = component_manager_.ResolveHandleAs<AiComponent>(light2_ai_component_handle);
        light2.AttachComponent(light2_ai_component_handle);
        light2_ai_component.Startup();
        
        GameComponentHandle light2_body_component_handle = component_manager_.GenerateBodyComponent();
        BodyComponent& light2_body_component = component_manager_.ResolveHandleAs<BodyComponent>(light2_body_component_handle);
        light2_body_component.position(glm::vec3(2.0f, 0.0f, 0.0f));
        light2.AttachComponent(light2_body_component_handle);
        light2_body_component.Startup();
        
        
        GameEntityHandle ship_handle = entity_manager_.GenerateGameEntity();
        GameEntity& ship = entity_manager_.ResolveHandle(ship_handle);
        
        GameComponentHandle ship_body_component_handle = component_manager_.GenerateBodyComponent();
        BodyComponent& ship_body_component = component_manager_.ResolveHandleAs<BodyComponent>(ship_body_component_handle);
        ship_body_component.max_speed(0.1f);
        ship_body_component.rotation_acceleration(0.0001f);
        
        ship.AttachComponent(ship_body_component_handle);
        ship_body_component.Startup();
        
        GameComponentHandle render_component_handle = component_manager_.GenerateRenderComponent(model_handle);
        RenderComponent& render_component = component_manager_.ResolveHandleAs<RenderComponent>(render_component_handle);
        ship.AttachComponent(render_component_handle);
        render_component.Startup();
        
        GameComponentHandle control_component_handle = component_manager_.GenerateControlComponent(keyboard_state_);
        ControlComponent& control_component = component_manager_.ResolveHandleAs<ControlComponent>(control_component_handle);
        ship.AttachComponent(control_component_handle);
        control_component.Startup();
        
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
                LOG_DEBUG << L"fps: " << fps << std::endl;
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
