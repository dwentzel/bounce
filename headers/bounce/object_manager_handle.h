#ifndef BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_
#define BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_

namespace bounce {
    
    template <typename T>
    class ObjectManagerHandle;
    
    template <typename T>
    T& ResolveHandle(const ObjectManagerHandle<T>&);
    
    template <typename T, typename Handle>
    T& ResolveHandleAs(const ObjectManagerHandle<Handle>&);
    
    template <typename T, typename Handle>
    ObjectManagerHandle<T> ConvertHandle(const ObjectManagerHandle<Handle>&);

    template <typename T>
    class ObjectManagerHandle {
    private:
        unsigned int index_;
        unsigned int type_;
        
    public:
        ObjectManagerHandle(unsigned int type, unsigned int index)
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
        
        T& Resolve() const
        {
            return ResolveHandle<T>(*this);
        }
        
        template <typename U>
        U& ResolveAs() const
        {
            return ResolveHandleAs<U, T>(*this);
        }
        
        template <typename U>
        ObjectManagerHandle<U> As()
        {
            return ConvertHandle<U, T>(*this);
        }
    };

}

#endif // BOUNCE_BOUNCE_OBJECT_MANAGER_HANDLE_
