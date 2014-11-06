#ifndef BOUNCE_EVENT_HPP_
#define BOUNCE_EVENT_HPP_

#include <memory>
#include "framework/lock_free_queue.h"
#include "keys.h"

namespace bounce {
    
    enum EventType {
        EVENT_KEYDOWN,
        EVENT_KEYUP,
        EVENT_QUIT
    };
    
    class Event {
    private:
        EventType type_;
    public:
        EventType type() const;
        virtual ~Event() = 0;
    protected:
        Event(EventType type);
    };
    
    inline EventType Event::type() const {
        return type_;
    }
    
    
    
    class KeyboardEvent: public Event {
    private:
        Keysym keysym_;
        
    protected:
        KeyboardEvent(EventType eventType, Keysym keysym);
        
    public:
        const Keysym& keysym() const;
        
    };
    
    inline const Keysym& KeyboardEvent::keysym() const {
        return keysym_;
    }
    
    class KeydownEvent: public KeyboardEvent {
    public:
        KeydownEvent(Keysym keysym);
    };
    
    class KeyupEvent: public KeyboardEvent {
    public:
        KeyupEvent(Keysym keysym);
    };
    
    class QuitEvent : public Event {
    public:
        QuitEvent();
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
