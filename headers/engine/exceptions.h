#ifndef BOUNCE_ENGINE_EXCEPTIONS_H_
#define BOUNCE_ENGINE_EXCEPTIONS_H_

#include "framework/exceptions.h"

namespace bounce {

    class ObjectManagerHandleException : public BounceException {
    public:
    	ObjectManagerHandleException();
    	ObjectManagerHandleException(const ObjectManagerHandleException& original);
    	virtual ~ObjectManagerHandleException();
        
    private:
        ObjectManagerHandleException& operator=(const ObjectManagerHandleException&) = delete;
        
    };

}

#endif // BOUNCE_ENGINE_EXCEPTIONS_H_
