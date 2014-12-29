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

    
    class KeyboardEvent : public Event {
    private:
        Keysym keysym_;
        
    protected:
        KeyboardEvent(EventType eventType, Keysym keysym);
        
    public:
        virtual ~KeyboardEvent();

        const Keysym& keysym() const;
        
    };
    
    inline const Keysym& KeyboardEvent::keysym() const {
        return keysym_;
    }
    
    class KeydownEvent : public KeyboardEvent {
    public:
        KeydownEvent(Keysym keysym);
        virtual ~KeydownEvent();
    };
    
    class KeyupEvent : public KeyboardEvent {
    public:
        KeyupEvent(Keysym keysym);
        virtual ~KeyupEvent();
    };
    
    class QuitEvent : public Event {
    public:
        QuitEvent();
        virtual ~QuitEvent();
    };

}


#endif // BOUNCE_ENGINE_EVENT_H_
