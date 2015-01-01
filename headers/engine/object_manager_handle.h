#ifndef BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
#define BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_

#include <limits>

namespace bounce {
    

    template <class T>
    class ObjectManagerHandle {
    private:
        static const unsigned int INVALID_INDEX;
        static const unsigned int INVALID_TYPE;
        
        unsigned int index_;
        unsigned int type_;
        
    public:
        static const ObjectManagerHandle invalid_handle;
        
        explicit ObjectManagerHandle(unsigned int type, unsigned int index)
        : index_(index), type_(type)
        {
            
        }
        
        unsigned int index() const
        {
            return index_;
        }
        
        unsigned int type() const
        {
            return type_;
        }
        
        bool invalid() const
        {
            return index_ == INVALID_INDEX;
        }
        
//        T& Resolve() const;
//        
//        template <typename U>
//        U& ResolveAs() const;
        
    };
    
//    template <class T>
//    T& ResolveHandle(const ObjectManagerHandle<T>&);
//    
//    template <class T, class Handle>
//    T& ResolveHandleAs(const ObjectManagerHandle<Handle>&);
//
//    template <class T>
//    T& ObjectManagerHandle<T>::Resolve() const
//    {
//        return ResolveHandle<T>(*this);
//    }
//    
//    template <class T>
//    template <typename U>
//    U& ObjectManagerHandle<T>::ResolveAs() const
//    {
//        return ResolveHandleAs<U, T>(*this);
//    }

    
    
    template <class T>
    const unsigned int ObjectManagerHandle<T>::INVALID_INDEX = std::numeric_limits<unsigned int>::max();
    
    template <class T>
    const unsigned int ObjectManagerHandle<T>::INVALID_TYPE = std::numeric_limits<unsigned int>::max();
    
    template <class T>
    const ObjectManagerHandle<T> ObjectManagerHandle<T>::invalid_handle = ObjectManagerHandle<T>(INVALID_TYPE, INVALID_INDEX);

}

#endif // BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
