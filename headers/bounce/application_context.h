#ifndef BOUNCE_APPLICATION_CONTEXT_H_
#define BOUNCE_APPLICATION_CONTEXT_H_

#include <string>
#include <memory>
#include "event.h"

namespace bounce {
    
    class ApplicationContext {
    private:
        EventManager event_manager_;
        void(*flush_)();
        void(*poll_)();

    public:
        ApplicationContext(void(*flush)(), void(*poll)()) : event_manager_(), flush_(flush), poll_(poll)
        {}
        
        ~ApplicationContext() {}
        
        EventManager* event_manager_ptr() { return &event_manager_; }
        EventManager& event_manager() { return event_manager_; }
        
        void flush() const { flush_(); }
        
        void Update() const { poll_(); }
        
    };
    
}


#endif // BOUNCE_APPLICATION_CONTEXT_H_ */
