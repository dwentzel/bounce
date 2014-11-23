#include "message.h"

bounce::Message::Message(MessageType message_type)
: message_type_(message_type)
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