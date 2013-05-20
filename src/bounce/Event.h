#ifndef EVENT_H_
#define EVENT_H_

#include "LockFreeQueue.h"

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

class KeyboardEvent: public Event {
protected:
	KeyboardEvent(EventType eventType) :
			Event(eventType) {
	}
};

class KeydownEvent: public KeyboardEvent {
public:
	KeydownEvent() : KeyboardEvent(EventType::Keydown) {

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
