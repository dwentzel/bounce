#include "event.h"


bounce::Event::Event(EventType type) : type_(type) {}

bounce::Event::~Event() {}

bounce::KeyboardEvent::KeyboardEvent(EventType eventType, Keysym keysym)
: Event(eventType), keysym_(keysym)
{}


bounce::KeydownEvent::KeydownEvent(Keysym keysym)
: KeyboardEvent(EVENT_KEYDOWN, keysym)
{}


bounce::KeyupEvent::KeyupEvent(Keysym keysym)
: KeyboardEvent(EVENT_KEYUP, keysym)
{}

bounce::QuitEvent::QuitEvent()
: Event(EVENT_QUIT)
{}
