#include "WindowsEventManager.hpp"

namespace bounce_win {
    WindowsEventManager::WindowsEventManager() {}

    WindowsEventManager::~WindowsEventManager() {}

    std::unique_ptr<bounce::Event> WindowsEventManager::pollEvent() {
        std::unique_ptr<bounce::Event> event;
        if (eventQueue.consume(event))
            return event;
        else
            return nullptr;
    }

    void WindowsEventManager::queueEvent(std::unique_ptr<bounce::Event> event) {
        eventQueue.produce(std::move(event));
    }

}