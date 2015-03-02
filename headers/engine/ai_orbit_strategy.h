#ifndef BOUNCE_ENGINE_AI_ORBIT_STRATEGY_
#define BOUNCE_ENGINE_AI_ORBIT_STRATEGY_

#include "control_strategy.h"

#include <glm/glm.hpp>

namespace bounce {

    class AiOrbitStrategy : public ControlStrategy {
    public:
        AiOrbitStrategy(float radius, int direction, const glm::vec3& center);
        AiOrbitStrategy(AiOrbitStrategy&& source) NOEXCEPT;
        ~AiOrbitStrategy();
        
        virtual void Update();
        
        virtual void HandleMessage(const Message& message);
        
        virtual std::unique_ptr<Message> CreateMessage() const;
        
        void position(const glm::vec3& value);
        
    private:
        float radius_;
        int direction_;
        glm::vec3 center_;
        glm::vec3 position_;
        glm::vec3 normal_;
        
    };

}

#endif // BOUNCE_ENGINE_AI_ORBIT_STRATEGY_
