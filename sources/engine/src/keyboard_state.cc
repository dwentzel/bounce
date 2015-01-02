#include "keyboard_state.h"

namespace std {
    template<>
    struct hash<bounce::Key> {
        size_t operator()(const bounce::Key &key) const {
            return std::hash<int>()(key);
        }
    };
    
}


bounce::KeyboardState::KeyboardState()
{
    for (int i = 0; i < NUM_KEYS; ++i) {
        pressed_keys_[i] = false;
    }
}

bounce::KeyboardState::~KeyboardState()
{
    
}

void bounce::KeyboardState::ProcessEvent(const KeyboardEvent& keyboardEvent)
{
    if (keyboardEvent.type() == EVENT_KEYDOWN) {
        pressed_keys_[keyboardEvent.keysym().sym] = true;
    }
    else if (keyboardEvent.type() == EVENT_KEYUP) {
        pressed_keys_[keyboardEvent.keysym().sym] = false;
    }
}

bool bounce::KeyboardState::IsDown(const Key& key) const
{
    return pressed_keys_[key];
}
