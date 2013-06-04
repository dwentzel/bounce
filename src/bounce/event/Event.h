#ifndef EVENT_H_
#define EVENT_H_

#include <memory>
#include "../LockFreeQueue.h"

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
	std::cout << "Delete event" << std::endl;
}

inline EventType Event::getType() const {
	return type;
}

enum Key {
	A, S, D, W
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

typedef LockFreeQueue<std::unique_ptr<Event>> EventQueue;

class EventManager {
public:
	virtual ~EventManager() = 0;
	virtual std::unique_ptr<Event> pollEvent() = 0;
};

inline EventManager::~EventManager() {
}

}

#endif
