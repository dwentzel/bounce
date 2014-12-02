/*
 * KeyboardState.cpp
 *
 *  Created on: 6 jun 2013
 *      Author: daniel
 */

#include "keyboard_state.h"

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

void KeyboardState::ProcessEvent(const KeyboardEvent& keyboardEvent)
{
	if (keyboardEvent.type() == EVENT_KEYDOWN) {
		pressed_keys_.insert(keyboardEvent.keysym().sym);
	}
	else if (keyboardEvent.type() == EVENT_KEYUP) {
		pressed_keys_.erase(keyboardEvent.keysym().sym);
	}
}

bool KeyboardState::IsDown(const Key& key) const {

	std::unordered_set<Key>::const_iterator foundKey = pressed_keys_.find(key);
	return foundKey != pressed_keys_.end();
}

} /* namespace bounce */
