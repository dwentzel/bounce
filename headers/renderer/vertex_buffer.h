#ifndef BOUNCE_RENDERER_VERTEX_BUFFER_H_
#define BOUNCE_RENDERER_VERTEX_BUFFER_H_

#include <cstddef>

namespace bounce {
    
    class VertexBuffer {
    private:
        size_t buffer_position_;
        unsigned long buffer_count_;
        size_t buffer_size_;
        void* buffer_;
        
    public:
        VertexBuffer();
        void AddData(void* data, size_t size);
        size_t current_size() const;
        const void* buffer() const;
    };
}

#endif // BOUNCE_RENDERER_VERTEX_BUFFER_H_
