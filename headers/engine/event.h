#ifndef BOUNCE_ENGINE_EVENT_H_
#define BOUNCE_ENGINE_EVENT_H_

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
        virtual ~Event();
    protected:
        Event(EventType type);
    };
    
    inline EventType Event::type() const {
        return type_;
    }
    
    
    
    class KeyboardEvent : public Event {
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
    
    class KeydownEvent : public KeyboardEvent {
    public:
        KeydownEvent(Keysym keysym);
    };
    
    class KeyupEvent : public KeyboardEvent {
    public:
        KeyupEvent(Keysym keysym);
    };
    
    class QuitEvent : public Event {
    public:
        QuitEvent();
    };

}

//template struct bounce_engine_EXPORT std::atomic < bounce::LockFreeQueue<bounce::EventPtr>::Node* >;



#endif // BOUNCE_ENGINE_EVENT_H_
