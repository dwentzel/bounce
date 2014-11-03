#ifndef BOUNCE_EVENT_HPP_
#define BOUNCE_EVENT_HPP_

#include <memory>
#include "lock_free_queue.h"

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
    
    enum Key {
        NO_KEY,
        A, S, D, W, Q, E
    };
    
    enum Modifier {
        NO_MODIFIER
    };
    
    struct Keysym {
        Key sym;
        Modifier mod;
    };
    
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
        
        EventPtr pollEvent() const;
        void queueEvent(EventPtr event) const;
        
    private:
        std::unique_ptr<EventQueue> event_queue_;
    };
    
    
    inline EventManager::EventManager() : event_queue_(new EventQueue) {}
    
    inline EventManager::~EventManager() {}
    
}

#endif
