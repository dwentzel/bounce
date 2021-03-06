#ifndef BOUNCE_ENGINE_KEYS_H_
#define BOUNCE_ENGINE_KEYS_H_

namespace bounce {
    
    enum Key {
        NO_KEY,
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_SPACE,
        KEY_ENTER,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        NUM_KEYS
    };
    
    enum Modifier {
        NO_MODIFIER
    };
    
    struct Keysym {
        Key sym;
        Modifier mod;
    };
    
}

#endif // BOUNCE_ENGINE_KEYS_H_
