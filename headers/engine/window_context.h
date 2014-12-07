#ifndef BOUNCE_ENGINE_WINDOW_CONTEXT_
#define BOUNCE_ENGINE_WINDOW_CONTEXT_

namespace bounce {

    class WindowContext {
    private:
        unsigned int width_;
        unsigned int height_;
        
    public:
        WindowContext(unsigned int width, unsigned int height);
        
        unsigned int width() const;
        unsigned int height() const;

    };

}

#endif // BOUNCE_ENGINE_WINDOW_CONTEXT_
