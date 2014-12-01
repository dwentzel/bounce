#ifndef BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_
#define BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_

namespace bounce {
    
    template <class T>
    class ObjectManagerHandle;
    
    template <class T>
    T& ResolveHandle(const ObjectManagerHandle<T>&);
    
    template <class T, class Handle>
    T& ResolveHandleAs(const ObjectManagerHandle<Handle>&);
//
//    template <typename T, typename Handle>
//    ObjectManagerHandle<T> ConvertHandle(const ObjectManagerHandle<Handle>&);

    template <class T>
    class ObjectManagerHandle {
    private:
        int index_;
        unsigned int type_;
        
    public:
        static const ObjectManagerHandle zero;
        
        ObjectManagerHandle(unsigned int type, int index)
        : index_(index), type_(type)
        {
            
        }
        
        int index() const
        {
            return index_;
        }
        
        unsigned int type() const
        {
            return type_;
        }
        
        T& Resolve() const
        {
            return ResolveHandle<T>(*this);
        }
        
        template <typename U>
        U& ResolveAs() const
        {
            return ResolveHandleAs<U, T>(*this);
        }
        
//        template <typename U>
//        ObjectManagerHandle<U> As()
//        {
//            return ConvertHandle<U, T>(*this);
//        }
    };
    
    template <class T>
    const ObjectManagerHandle<T> ObjectManagerHandle<T>::zero = ObjectManagerHandle<T>(-1, -1);

}

#endif // BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_
