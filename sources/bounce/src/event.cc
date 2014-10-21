#include "event.h"

namespace bounce {

    EventPtr EventManager::pollEvent() const
    {
        EventPtr event;

        if (event_queue_->consume(event)) {
            return event;
        }
        else {
            return nullptr;
        }
    }

    void EventManager::queueEvent(EventPtr event) const {
        event_queue_->produce(std::move(event));
    }
}