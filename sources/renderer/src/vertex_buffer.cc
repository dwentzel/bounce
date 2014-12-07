#include "vertex_buffer.h"
#include <cstring>
#include <cstdlib>

bounce::VertexBuffer::VertexBuffer()
{
    buffer_position_ = 0;
    buffer_count_ = 20000;
    buffer_size_ = buffer_count_ * sizeof(float);
    buffer_ = new char[buffer_size_];
}

void bounce::VertexBuffer::AddData(void *data, size_t size)
{
    char* ptr = (char*)buffer_;
    
    memcpy(ptr + buffer_position_, data, size);
    
    buffer_position_ += size;// / sizeof(float);
    
//    float buffer_arr[200];
//    memcpy(buffer_arr, buffer_, buffer_position_);
//
//    float data_arr[3];
//    memcpy(data_arr, data, size);

}

size_t bounce::VertexBuffer::current_size() const
{
    return buffer_position_;// * sizeof(float);
}

const void* bounce::VertexBuffer::buffer() const
{
    return buffer_;
}