#include "message.h"

bounce::Message::Message(MessageType message_type)
: message_type_(message_type)
{
    
}

bounce::AccelerationChangedMessage::AccelerationChangedMessage(int yaw, int pitch, int roll)
: Message(ACCELERATION_CHANGED_MESSAGE), yaw_(yaw), pitch_(pitch), roll_(roll)
{
    
}

bounce::PositionChangedMessage::PositionChangedMessage(const glm::vec3& position)
: Message(POSITION_CHANGED_MESSAGE), position_(position)
{
    
}

const glm::vec3& bounce::PositionChangedMessage::position() const
{
    return position_;
}