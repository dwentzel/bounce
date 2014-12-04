#ifndef BOUNCE_FRAMEWORK_OBJECT_CACHE_
#define BOUNCE_FRAMEWORK_OBJECT_CACHE_

#include <vector>
#include <memory>

namespace bounce {
    
    template<class T>
    class ObjectCache {
    private:
        std::vector<T> cache_;
        
    public:
        typedef typename std::vector<T>::iterator iterator;
        typedef typename std::vector<T>::const_iterator const_iterator;
        
        
        ObjectCache();
        
        iterator begin();
        const_iterator begin() const;
        
        iterator end();
        const_iterator end() const;
        
        template<class... FactoryArgs>
        unsigned int GenerateObject(FactoryArgs&&...);

        T& GetObject(unsigned int handle);
        const T& GetObject(unsigned int handle) const;
        
    };

    
    template<class T>
    ObjectCache<T>::ObjectCache()
    {
        
    }
    
    template<class T>
    typename ObjectCache<T>::iterator ObjectCache<T>::begin()
    {
        return cache_.begin();
    }
    
    template<class T>
    typename ObjectCache<T>::const_iterator ObjectCache<T>::begin() const
    {
        return cache_.begin();
    }
    
    template<class T>
    typename ObjectCache<T>::iterator ObjectCache<T>::end()
    {
        return cache_.end();
    }
    
    template<class T>
    typename ObjectCache<T>::const_iterator ObjectCache<T>::end() const
    {
        return cache_.end();
    }
    
    template<class T>
    template<class... FactoryArgs>
    unsigned int ObjectCache<T>::GenerateObject(FactoryArgs&&... args)
    {
        unsigned int index = cache_.size();
        
        cache_.push_back(T::Create(std::forward<FactoryArgs>(args)...));
        
        return index;
    }
    
    template<class T>
    T& ObjectCache<T>::GetObject(unsigned int handle)
    {
        return cache_[handle];
    }

    template<class T>
    const T& ObjectCache<T>::GetObject(unsigned int handle) const
    {
        return cache_[handle];
    }
    
//    template <class T>
//    class ObjectCacheHandle {
//    private:
//        unsigned int index_;
//        unsigned int type_;
//    public:
//        ObjectCacheHandle(unsigned int index, unsigned int type) : index_(index), type_(type)
//        {
//            
//        }
//        
//        unsigned int index() const
//        {
//            return index_;
//        }
//        
//        size_t type() const
//        {
//            return type_;
//        }
//    };
    
//    template <class Handle, class... Ts>
//    class CompositeCache {
//    private:
//        std::tuple<ObjectCache<Ts>...> caches_;
//    public:
//        template <size_t k>
//        ObjectCacheHandle<Handle> Generate();
//        
//        template <unsigned int type>
//        Handle& Resolve(ObjectCacheHandle<Handle> handle);
//    };
//    
//    template <class Handle, class... Ts>
//    template <size_t k>
//    ObjectCacheHandle<Handle> CompositeCache<Handle, Ts...>::Generate()
//    {
//        unsigned int index = std::get<k>(caches_).GenerateObject();
//        ObjectCacheHandle<Handle> handle(index, k);
//        return handle;
//    }
//    
//    template <class Handle, class... Ts>
//    template <unsigned int type>
//    Handle& CompositeCache<Handle, Ts...>::Resolve(ObjectCacheHandle<Handle> handle)
//    {
//        return std::get<type>(caches_).GetObject(handle.index());
//    }
    
    
}

#endif // BOUNCE_FRAMEWORK_OBJECT_CACHE_
