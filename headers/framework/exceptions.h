#ifndef BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_
#define BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_

#include <exception>

namespace bounce {

    class BounceException : public std::exception {
    public:
    	BounceException();
        BounceException(const BounceException& other);
        BounceException(BounceException&& other);
        
    	virtual ~BounceException();
        
    private:
        BounceException& operator=(const BounceException&) = delete;
        BounceException& operator=(BounceException&&) = delete;

    };

    class ObjectNotFoundException : public BounceException {
        
    };
}

#endif // BOUNCE_FRAMEWORK_BOUNCE_EXCEPTION_
