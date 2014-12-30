#include "event.h"


bounce::Event::Event(EventType type) : type_(type)
{

}

bounce::Event::~Event()
{

}

bounce::EventType bounce::Event::type() const
{
    return type_;
}



bounce::KeyboardEvent::KeyboardEvent(EventType eventType, Keysym keysym)
: Event(eventType), keysym_(keysym)
{

}

bounce::KeyboardEvent::KeyboardEvent(const KeyboardEvent&) = default;

bounce::KeyboardEvent::~KeyboardEvent()
{

}



bounce::KeydownEvent::KeydownEvent(Keysym keysym)
: KeyboardEvent(EVENT_KEYDOWN, keysym)
{

}

bounce::KeydownEvent::~KeydownEvent()
{

}



bounce::KeyupEvent::KeyupEvent(Keysym keysym)
: KeyboardEvent(EVENT_KEYUP, keysym)
{

}

bounce::KeyupEvent::~KeyupEvent()
{

}



bounce::QuitEvent::QuitEvent()
: Event(EVENT_QUIT)
{

}

bounce::QuitEvent::~QuitEvent()
{

}
