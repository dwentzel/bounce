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
    protected:
        explicit Event(EventType type);
        Event(const Event& other);
        
    public:
        virtual ~Event();
        EventType type() const;
        
    private:
        EventType type_;
        
    private:

        Event& operator=(const Event&);
    };

    
    
    class KeyboardEvent : public Event {
    protected:
        KeyboardEvent(EventType eventType, Keysym keysym);
        
    public:
        KeyboardEvent(const KeyboardEvent&);
        virtual ~KeyboardEvent();

        const Keysym& keysym() const;
        
    private:
        Keysym keysym_;
        
    private:
        KeyboardEvent& operator=(const KeyboardEvent&) = delete;

    };
    
    inline const Keysym& KeyboardEvent::keysym() const {
        return keysym_;
    }
    
    
    
    class KeydownEvent : public KeyboardEvent {
    public:
        explicit KeydownEvent(Keysym keysym);
        virtual ~KeydownEvent();
    };
    
}

namespace bounce {
    
    class KeyupEvent : public KeyboardEvent {
    public:
        explicit KeyupEvent(Keysym keysym);
        virtual ~KeyupEvent();
    };
    
    
    
    class QuitEvent : public Event {
    public:
        QuitEvent();
        virtual ~QuitEvent();
    };

}


#endif // BOUNCE_ENGINE_EVENT_H_
