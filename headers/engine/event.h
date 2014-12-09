#ifndef BOUNCE_ENGINE_EVENT_H_
#define BOUNCE_ENGINE_EVENT_H_

#include "keys.h"

#include "bounce_engine_export.h"

namespace bounce {
    
    enum EventType {
        EVENT_KEYDOWN,
        EVENT_KEYUP,
        EVENT_QUIT
    };
    
    class bounce_engine_EXPORT Event {
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
    
    
    
    class bounce_engine_EXPORT KeyboardEvent : public Event {
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
    
    class bounce_engine_EXPORT KeydownEvent : public KeyboardEvent {
    public:
        KeydownEvent(Keysym keysym);
    };
    
    class bounce_engine_EXPORT KeyupEvent : public KeyboardEvent {
    public:
        KeyupEvent(Keysym keysym);
    };
    
    class bounce_engine_EXPORT QuitEvent : public Event {
    public:
        QuitEvent();
    };

}

//template struct bounce_engine_EXPORT std::atomic < bounce::LockFreeQueue<bounce::EventPtr>::Node* >;



#endif // BOUNCE_ENGINE_EVENT_H_
