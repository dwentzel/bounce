#ifndef EVENT_H_
#define EVENT_H_

namespace bounce {

class Event {
private:

public:
	enum EventType {
		Quit
	};

	EventType type;

};


class EventManager {
public:
	virtual ~EventManager() = 0;
	virtual Event* pollEvent() const = 0;
};

inline EventManager::~EventManager() {}

}

#endif
