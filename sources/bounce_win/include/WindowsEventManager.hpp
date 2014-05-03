#ifndef WINDOWSEVENTMANAGER_HPP_
#define WINDOWSEVENTMANAGER_HPP_

#include <memory>
#include "bounce\Event.hpp"

namespace bounce_win {

    class WindowsEventManager : public bounce::EventManager {
    public:
        WindowsEventManager();
        ~WindowsEventManager();

        virtual std::unique_ptr<bounce::Event> pollEvent();
        void queueEvent(std::unique_ptr<bounce::Event> event);
    private:
        bounce::EventQueue eventQueue;
    };

}


#endif //WINDOWSEVENTMANAGER_HPP_