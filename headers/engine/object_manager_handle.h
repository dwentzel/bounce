#ifndef BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
#define BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_

#include <limits>

namespace bounce {
    
    template <class T>
    class ObjectManagerHandle {
    public:
        typedef unsigned int index_t;
        typedef unsigned short type_t;
        
        static const ObjectManagerHandle invalid_handle;
        
        ObjectManagerHandle(type_t type, index_t index);
        
        index_t index() const;
        type_t type() const;
        bool is_valid() const;
        
    private:
        static const index_t INVALID_INDEX{std::numeric_limits<index_t>::max()};
        
        ObjectManagerHandle(index_t index);
        
        index_t index_;
    };
    
    template <class T>
    ObjectManagerHandle<T>::ObjectManagerHandle(index_t index)
    : index_(index)
    {
    }
    
    template <class T>
    ObjectManagerHandle<T>::ObjectManagerHandle(type_t type, index_t index)
    : index_((index << 4) | (type & 0x0F))
    {
    }
    
    template <class T>
    typename ObjectManagerHandle<T>::index_t ObjectManagerHandle<T>::index() const
    {
        return index_ >> 4;
    }
    
    template <class T>
    typename ObjectManagerHandle<T>::type_t ObjectManagerHandle<T>::type() const
    {
        return index_ & 0x0F;
    }
    
    template <class T>
    bool ObjectManagerHandle<T>::is_valid() const
    {
        return index_ != INVALID_INDEX;
    }
    
//    template <class T>
//    const typename ObjectManagerHandle<T>::index_t ObjectManagerHandle<T>::INVALID_INDEX = std::numeric_limits<index_t>::max();
    
    template <class T>
    const ObjectManagerHandle<T> ObjectManagerHandle<T>::invalid_handle{INVALID_INDEX};

}

#endif // BOUNCE_ENGINE_OBJECT_MANAGER_HANDLE_
