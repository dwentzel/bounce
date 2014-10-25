#ifndef BOUNCE_GAME_COMPONENT_H
#define BOUNCE_GAME_COMPONENT_H

namespace bounce{
    
    class GameComponent {
    private:
        
    public:
        virtual void startup() = 0;
        
        virtual void shutdown() = 0;
        
        virtual void update() = 0;
    };
    
    class RenderComponent : public GameComponent
    {
    public:
        virtual void startup();
        
        virtual void shutdown();
        
        virtual void update();
    };
}

#endif