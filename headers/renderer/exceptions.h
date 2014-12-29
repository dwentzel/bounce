#ifndef BOUNCE_RENDERER_EXCEPTIONS_H_
#define BOUNCE_RENDERER_EXCEPTIONS_H_

#include "framework/exceptions.h"

namespace bounce {

    class RendererException : public BounceException {
    private:
    	RendererException& operator=(const RendererException&) = delete;

    public:
    	RendererException();
    	RendererException(const RendererException& original);

    	virtual ~RendererException();
    };

}

#endif // BOUNCE_RENDERER_EXCEPTIONS_H_
