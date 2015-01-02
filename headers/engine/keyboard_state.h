#ifndef BOUNCE_ENGINE_KEYBOARDSTATE_H_
#define BOUNCE_ENGINE_KEYBOARDSTATE_H_

#include <memory>
#include <unordered_set>
#include "event.h"

namespace bounce {

    class KeyboardState {
    public:
        KeyboardState();
        ~KeyboardState();

        void ProcessEvent(const KeyboardEvent& event);

        bool IsDown(const Key& key) const;
    
    private:
        bool pressed_keys_[NUM_KEYS];
    };

}
#endif // BOUNCE_ENGINE_KEYBOARDSTATE_H_
