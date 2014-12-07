#ifndef BOUNCE_ENGINE_APPLICATION_CONTEXT_H_
#define BOUNCE_ENGINE_APPLICATION_CONTEXT_H_

#include <string>
#include "event.h"
#include "window_context.h"

#include "bounce_engine_export.h"

namespace bounce {
    
    class bounce_engine_EXPORT ApplicationContext{
    private:
        EventManager event_manager_;
        
    protected:
        ApplicationContext();
        
    public:
        virtual ~ApplicationContext() = 0;
        
        EventManager* event_manager_ptr() { return &event_manager_; }
        EventManager& event_manager() { return event_manager_; }
        
        virtual void Flush() const = 0;
        
        virtual void Update() const = 0;
        
        virtual void CreateApplicationWindow(const WindowContext& window_context) = 0;
        
        virtual const std::string& root_path() const = 0;
    };
    
}


#endif // BOUNCE_ENGINE_APPLICATION_CONTEXT_H_ */
