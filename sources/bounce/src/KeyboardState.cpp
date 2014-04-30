/*
 * KeyboardState.cpp
 *
 *  Created on: 6 jun 2013
 *      Author: daniel
 */

#include "KeyboardState.h"

namespace std {
	template<>
	struct hash<bounce::Key> {
		size_t operator()(const bounce::Key &key) const {
			return std::hash<int>()(key);
		}
	};

}

namespace bounce {

KeyboardState::KeyboardState() {


}

KeyboardState::~KeyboardState() {

}

void KeyboardState::processEvent(const KeyboardEvent& keyboardEvent) {
	if (keyboardEvent.getType() == EventType::Keydown) {
		pressedKeys.insert(keyboardEvent.getKeysym().sym);
	}
	else if (keyboardEvent.getType() == EventType::Keyup) {
		pressedKeys.erase(keyboardEvent.getKeysym().sym);
	}
}

bool KeyboardState::isDown(const Key& key) {

	std::unordered_set<Key>::const_iterator foundKey = pressedKeys.find(key);
	return foundKey != pressedKeys.end();
}

} /* namespace bounce */
