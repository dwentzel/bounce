#ifndef BOUNCE_BOUNCE_POSITION_COMPONENT_
#define BOUNCE_BOUNCE_POSITION_COMPONENT_

#include "game_component.h"

namespace bounce {

    class PositionComponent : public GameComponent {
    private:
        glm::vec3 position_;
        
    public:
        PositionComponent(const glm::vec3& position);
        
        virtual void Startup();
        virtual void Shutdown();
        virtual void Update();
        
//        virtual void HandleMessage(const Message& message);

    };

}

#endif // BOUNCE_BOUNCE_POSITION_COMPONENT_
