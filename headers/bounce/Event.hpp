#ifndef BOUNCE_EVENT_HPP_
#define BOUNCE_EVENT_HPP_

#include <memory>
#include "LockFreeQueue.hpp"

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
	A, S, D, W
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

typedef std::unique_ptr<Event> EventPtr;
typedef LockFreeQueue<EventPtr> EventQueue;

class EventManager {
public:
    EventManager();
    ~EventManager();

    EventPtr pollEvent();
    void queueEvent(EventPtr event);

private:
    EventQueue eventQueue;
};


inline EventManager::EventManager() {}

inline EventManager::~EventManager() {}

}

#endif
