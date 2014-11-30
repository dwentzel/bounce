#ifndef BOUNCE_APPLICATION_CONTEXT_H_
#define BOUNCE_APPLICATION_CONTEXT_H_

#include <string>
#include "event.h"
#include "window_context.h"

namespace bounce {
    
    class ApplicationContext {
    private:
        EventManager event_manager_;
        
    protected:
        ApplicationContext();
        
    public:
        
        virtual ~ApplicationContext() = 0;
        
        EventManager* event_manager_ptr() { return &event_manager_; }
        EventManager& event_manager() { return event_manager_; }
        
        virtual void Flush() const = 0;// { flush_(); }
        
        virtual void Update() const = 0;// { poll_(); }
        
        virtual void CreateWindow(const WindowContext& window_context) = 0;
        
        virtual const std::string& root_path() const = 0;
    };
    
}


#endif // BOUNCE_APPLICATION_CONTEXT_H_ */
