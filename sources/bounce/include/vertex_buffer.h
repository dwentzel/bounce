#ifndef BOUNCE_VERTEX_BUFFER_H_
#define BOUNCE_VERTEX_BUFFER_H_

#include <cstddef>

namespace bounce {
    
    class VertexBuffer {
    private:
        int buffer_position_;
        int buffer_count_;
        size_t buffer_size_;
        void* buffer_;
        
    public:
        VertexBuffer();
        void AddData(void* data, size_t size);
        size_t current_size() const;
        const void* buffer() const;
    };
    
}

#endif // BOUNCE_VERTEX_BUFFER_H_