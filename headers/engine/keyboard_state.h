#ifndef BOUNCE_ENGINE_KEYBOARDSTATE_H_
#define BOUNCE_ENGINE_KEYBOARDSTATE_H_

#include <memory>
#include <unordered_set>
#include "event.h"

namespace bounce {

class KeyboardState {
private:
	std::unordered_set<Key, std::hash<int>> pressed_keys_;

public:
	KeyboardState();
	virtual ~KeyboardState();

	void ProcessEvent(const KeyboardEvent& event);

	bool IsDown(const Key& key) const;
};

}
#endif // BOUNCE_ENGINE_KEYBOARDSTATE_H_
