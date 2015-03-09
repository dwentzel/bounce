#ifndef BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
#define BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_

#include <limits>

namespace bounce {
    
    template <class T>
    class ObjectManagerHandle {
    public:
        typedef unsigned int index_t;
        typedef unsigned int type_t;
        
        static const ObjectManagerHandle invalid_handle;
        
        ObjectManagerHandle(type_t type, index_t index);
        
        index_t index() const;
        type_t type() const;
        bool is_valid() const;
        
    private:
        static const index_t INVALID_INDEX;
        static const type_t INVALID_TYPE;
        
        index_t index_;
        type_t type_;
    };
    
    template <class T>
    ObjectManagerHandle<T>::ObjectManagerHandle(type_t type, index_t index)
    : index_(index), type_(type)
    {
    }
    
    template <class T>
    typename ObjectManagerHandle<T>::index_t ObjectManagerHandle<T>::index() const
    {
        return index_;
    }
    
    template <class T>
    typename ObjectManagerHandle<T>::type_t ObjectManagerHandle<T>::type() const
    {
        return type_;
    }
    
    template <class T>
    bool ObjectManagerHandle<T>::is_valid() const
    {
        return index_ != INVALID_INDEX;
    }
    
    template <class T>
    const typename ObjectManagerHandle<T>::index_t ObjectManagerHandle<T>::INVALID_INDEX = std::numeric_limits<index_t>::max();
    
    template <class T>
    const typename ObjectManagerHandle<T>::type_t ObjectManagerHandle<T>::INVALID_TYPE = std::numeric_limits<type_t>::max();
    
    template <class T>
    const ObjectManagerHandle<T> ObjectManagerHandle<T>::invalid_handle{INVALID_TYPE, INVALID_INDEX};

}

#endif // BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
