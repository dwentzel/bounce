#ifndef EVENT_H_
#define EVENT_H_

#include "../LockFreeQueue.h"

namespace bounce {

enum EventType {
	Keydown, Quit
};

class Event {
private:
	EventType type;
public:
	EventType getType();
protected:
	Event(EventType type) :
			type(type) {
	}

	virtual ~Event() = 0;
};

inline Event::~Event() {

}

inline EventType Event::getType() {
	return type;
}

enum Key {
	A,
	S,
	D,
	W
};

enum Modifier {

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
	KeydownEvent(Keysym keysym) : KeyboardEvent(EventType::Keydown, keysym) {

	}
};

typedef LockFreeQueue<Event*> EventQueue;

class EventManager {
public:
	virtual ~EventManager() = 0;
	virtual Event* pollEvent() = 0;
};

inline EventManager::~EventManager() {
}

}

#endif
