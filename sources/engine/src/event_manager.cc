#include "event_manager.h"

#include "framework/lock_free_queue.h"

namespace bounce {
    
    typedef bounce::LockFreeQueue<bounce::EventPtr> EventQueue;

}

class bounce::EventManagerImpl {
private:
    LockFreeQueue<EventPtr> event_queue_;

public:
    EventPtr PollEvent();
    void QueueEvent(EventPtr event);
};

bounce::EventManager::EventManager()
: impl_(new EventManagerImpl())
{
}
        
bounce::EventPtr bounce::EventManagerImpl::PollEvent()
{
    EventPtr event;
    
    if (event_queue_.consume(event)) {
        return event;
    }
    else {
        return nullptr;
    }
}

void bounce::EventManagerImpl::QueueEvent(EventPtr event)
{
    event_queue_.produce(std::move(event));
}

bounce::EventManager::~EventManager()
{
    delete impl_;
}


bounce::EventPtr bounce::EventManager::PollEvent()
{
    return impl_->PollEvent();
}

void bounce::EventManager::QueueEvent(EventPtr event)
{
    impl_->QueueEvent(std::move(event));
}
