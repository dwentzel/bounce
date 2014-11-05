#ifndef BOUNCE_GAME_SYSTEM_H
#define BOUNCE_GAME_SYSTEM_H

namespace bounce {
    
    class GameSystem {
    public:
        virtual void startup() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;
    };
    
}

#endif