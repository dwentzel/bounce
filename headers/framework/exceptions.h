#ifndef BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_
#define BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_

#include <exception>

namespace bounce {

    class BounceException : public std::exception {
    private:
    	BounceException& operator=(const BounceException&) = delete;

    public:
    	BounceException();
        BounceException(const BounceException&);
    	virtual ~BounceException();
    };

    class ObjectNotFoundException : public BounceException {
        
    };
}

#endif // BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_
