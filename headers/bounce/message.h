#ifndef BOUNCE_MESSAGE_H_
#define BOUNCE_MESSAGE_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace bounce {
    
    enum MessageType {
        POSITION_CHANGED_MESSAGE,
        ACCELERATION_CHANGED_MESSAGE
    };
    
    
    class Message {
    private:
        const MessageType message_type_;
        
    protected:
        Message(MessageType message_type);
        
    public:
        MessageType message_type() const;
    };
    
    inline MessageType Message::message_type() const {
        return message_type_;
    }
    
    class AccelerationChangedMessage : public Message {
    private:
        float yaw_;
        float pitch_;
        float roll_;
        
    public:
        AccelerationChangedMessage(float yaw, float pitch, float roll);
        
        float yaw() const;
        float pitch() const;
        float roll() const;
    };
        
    inline float AccelerationChangedMessage::yaw() const
    {
        return yaw_;
    }
    
    inline float AccelerationChangedMessage::pitch() const
    {
        return pitch_;
    }
    
    inline float AccelerationChangedMessage::roll() const
    {
        return roll_;
    }
    
    class PositionChangedMessage : public Message {
    private:
        const glm::vec3 position_;
        
    public:
        PositionChangedMessage(const glm::vec3& position);
        
        const glm::vec3& position() const;
    };
    
}

#endif // BOUNCE_MESSAGE_H_