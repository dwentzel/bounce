#include "event.h"

namespace bounce {

    
    EventManager::EventManager()
    {
//        event_queue_ = new EventQueue();
    }
    
    EventManager::~EventManager()
    {
    
    }
    
    
    EventPtr EventManager::PollEvent()
    {
        EventPtr event;

        if (event_queue_.consume(event)) {
            return event;
        }
        else {
            return nullptr;
        }
    }

    void EventManager::QueueEvent(EventPtr event)
    {
        event_queue_.produce(std::move(event));
    }
}