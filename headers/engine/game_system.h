#ifndef BOUNCE_ENGINE_GAME_SYSTEM_H_
#define BOUNCE_ENGINE_GAME_SYSTEM_H_

namespace bounce {
    
    class GameSystem {
    public:
        virtual ~GameSystem() = 0;
        
        virtual void Startup() = 0;
        virtual void Shutdown() = 0;
        virtual void Update(float delta_time) = 0;
    };
    
}

#endif // BOUNCE_ENGINE_GAME_SYSTEM_H_
