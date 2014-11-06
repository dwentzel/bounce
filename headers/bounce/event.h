#ifndef BOUNCE_EVENT_HPP_
#define BOUNCE_EVENT_HPP_

#include <memory>
#include "framework/lock_free_queue.h"
#include "keys.h"

namespace bounce {
    
    enum EventType {
        Keydown, Keyup, Quit
    };
    
    class Event {
    private:
        EventType type;
    public:
        EventType getType() const;
        virtual ~Event() = 0;
    protected:
        Event(EventType type) :
        type(type) {
        }
    };
    
    inline Event::~Event() {
        //std::cout << "Delete event" << std::endl;
    }
    
    inline EventType Event::getType() const {
        return type;
    }
    
    
    class KeyboardEvent: public Event {
    private:
        Keysym keysym;
        
    protected:
        KeyboardEvent(EventType eventType, Keysym keysym) :
        Event(eventType), keysym(keysym) {
        }
        
    public:
        const Keysym& getKeysym() const;
    };
    
    inline const Keysym& KeyboardEvent::getKeysym() const {
        return keysym;
    }
    
    class KeydownEvent: public KeyboardEvent {
    public:
        KeydownEvent(Keysym keysym) :
        KeyboardEvent(EventType::Keydown, keysym) {
            
        }
    };
    
    class KeyupEvent: public KeyboardEvent {
    public:
        KeyupEvent(Keysym keysym) :
        KeyboardEvent(EventType::Keyup, keysym) {
            
        }
    };
    
    class QuitEvent : public Event {
    public:
        QuitEvent() : Event(Quit) {}
    };
    
    typedef std::unique_ptr<Event> EventPtr;
    typedef LockFreeQueue<EventPtr> EventQueue;
    
    class EventManager {
    public:
        EventManager();
        ~EventManager();
        
        EventPtr PollEvent();
        void QueueEvent(EventPtr event);
        
    private:
        EventQueue event_queue_;
    };
}

#endif
