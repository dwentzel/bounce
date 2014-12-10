#ifndef BOUNCE_ENGINE_EVENT_MANAGER_H_
#define BOUNCE_ENGINE_EVENT_MANAGER_H_

#include <memory>
#include "event.h"

namespace bounce {
    
    typedef std::unique_ptr<Event> EventPtr;
    
    class EventManagerImpl;
    
    class EventManager {
    private:
        EventManagerImpl* impl_;
        
    public:
        EventManager();
        ~EventManager();
        
        EventPtr PollEvent();
        void QueueEvent(EventPtr event);
        
    };
}

#endif // BOUNCE_ENGINE_EVENT_MANAGER_H_
