/*
 * KeyboardState.h
 *
 *  Created on: 6 jun 2013
 *      Author: daniel
 */

#ifndef KEYBOARDSTATE_H_
#define KEYBOARDSTATE_H_

#include <memory>
#include <unordered_set>
#include "Event.h"

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

} /* namespace bounce */
#endif /* KEYBOARDSTATE_H_ */
