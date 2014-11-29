#ifndef BOUNCE_BOUNCE_AI_ORBIT_STRATEGY_
#define BOUNCE_BOUNCE_AI_ORBIT_STRATEGY_

#include "ai_strategy.h"

#include <glm/glm.hpp>

namespace bounce {

    class AiOrbitStrategy : public AiStrategy {
    private:
        float radius_;
        int direction_;
        
        glm::vec3 center_;
        
        glm::vec3 position_;

    public:
        AiOrbitStrategy(ObjectManagerHandle<AiComponent> owner, float radius, int direction, const glm::vec3& center);
        
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
        
        void position(const glm::vec3& value);
    };

}

#endif // BOUNCE_BOUNCE_AI_ORBIT_STRATEGY_
