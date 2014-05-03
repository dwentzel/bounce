#include "Event.hpp"

namespace bounce {

    EventPtr EventManager::pollEvent() {
        EventPtr event;

        if (eventQueue.consume(event)) {
            return event;
        }
        else {
            return nullptr;
        }
    }

    void EventManager::queueEvent(EventPtr event) {
        eventQueue.produce(std::move(event));
    }
}