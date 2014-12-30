#ifndef BOUNCE_ENGINE_MESSAGE_H_
#define BOUNCE_ENGINE_MESSAGE_H_

#include "bounce.h"

#include "contrib/disable_clang_warnings.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "contrib/enable_clang_warnings.h"

namespace bounce {
    
    enum MessageType {
        POSITION_CHANGED_MESSAGE,
        ORIENTATION_CHANGED_MESSAGE,
        MODEL_MATRIX_CHANGED_MESSAGE,
        ACCELERATION_CHANGED_MESSAGE
    };
    
    
    class Message {
    private:
        const MessageType message_type_;
        
        Message(const Message&) = delete;
        Message& operator=(const Message&) = delete;
        Message& operator=(Message&&) = delete;

    protected:
        Message(MessageType message_type);
        
    public:
        virtual ~Message() NOEXCEPT;

        MessageType message_type() const;
    };
    
    inline MessageType Message::message_type() const {
        return message_type_;
    }
    
    class AccelerationChangedMessage : public Message {
    private:
        int yaw_;
        int pitch_;
        int roll_;
        
        glm::vec3 direction_;
        
    public:
        AccelerationChangedMessage(int yaw, int pitch, int roll, const glm::vec3& direction);
        
        int yaw() const;
        int pitch() const;
        int roll() const;
        
        const glm::vec3& direction() const;
    };
        
    inline int AccelerationChangedMessage::yaw() const
    {
        return yaw_;
    }
    
    inline int AccelerationChangedMessage::pitch() const
    {
        return pitch_;
    }
    
    inline int AccelerationChangedMessage::roll() const
    {
        return roll_;
    }
    
    inline const glm::vec3& AccelerationChangedMessage::direction() const
    {
        return direction_;
    }
    
    class PositionChangedMessage : public Message {
    private:
        const glm::vec3 position_;
        
    public:
        PositionChangedMessage(const glm::vec3& position);
        
        const glm::vec3& position() const;
    };
    
    class OrientationChangedMessage : public Message {
    private:
        const glm::quat& orientation_;
        
    public:
        OrientationChangedMessage(const glm::quat& orientation);
        
        const glm::quat& orientation() const;
    };
    
    inline OrientationChangedMessage::OrientationChangedMessage(const glm::quat& orientation)
    : Message(ORIENTATION_CHANGED_MESSAGE), orientation_(orientation)
    {
        
    }
    
    inline const glm::quat& OrientationChangedMessage::orientation() const
    {
        return orientation_;
    }
    
}

#endif // BOUNCE_ENGINE_MESSAGE_H_
