#ifndef BOUNCE_GAME_SYSTEM_H
#define BOUNCE_GAME_SYSTEM_H

namespace bounce {
    
    class GameSystem {
    public:
        virtual void Startup() = 0;
        virtual void Shutdown() = 0;
        virtual void Update(float delta_time) = 0;
    };
    
}

#endif