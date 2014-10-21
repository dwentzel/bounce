/*
 * KeyboardState.h
 *
 *  Created on: 6 jun 2013
 *      Author: daniel
 */

#ifndef BOUNCE_KEYBOARDSTATE_H_
#define BOUNCE_KEYBOARDSTATE_H_

#include <memory>
#include <unordered_set>
#include "event.h"

namespace bounce {

class KeyboardState {
private:
	std::unordered_set<Key, std::hash<int>> pressedKeys;

public:
	KeyboardState();
	virtual ~KeyboardState();

	void processEvent(const KeyboardEvent& event);

	bool isDown(const Key& key);
};

}
#endif // BOUNCE_KEYBOARDSTATE_H_
