#ifndef BOUNCE_FRAMEWORK_OBJECT_CACHE_
#define BOUNCE_FRAMEWORK_OBJECT_CACHE_

#include <vector>

namespace bounce {
    
    template<typename T>
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
        
        template<typename... FactoryArgs>
        unsigned int GenerateObject(FactoryArgs&&...);
        T& GetObject(unsigned int handle);
        
    };

    
    template<typename T>
    ObjectCache<T>::ObjectCache()
    {
        
    }
    
    template<typename T>
    typename ObjectCache<T>::iterator ObjectCache<T>::begin()
    {
        return cache_.begin();
    }
    
    template<typename T>
    typename ObjectCache<T>::const_iterator ObjectCache<T>::begin() const
    {
        return cache_.begin();
    }
    
    template<typename T>
    typename ObjectCache<T>::iterator ObjectCache<T>::end()
    {
        return cache_.end();
    }
    
    template<typename T>
    typename ObjectCache<T>::const_iterator ObjectCache<T>::end() const
    {
        return cache_.end();
    }
    
    template<typename T>
    template<typename... FactoryArgs>
    unsigned int ObjectCache<T>::GenerateObject(FactoryArgs&&... args)
    {
        unsigned int index = cache_.size();
        
        cache_.push_back(T::Create(args...));
        
        return index;
    }
    
    template<typename T>
    T& ObjectCache<T>::GetObject(unsigned int handle)
    {
        return cache_[handle];
    }
    
}

#endif // BOUNCE_FRAMEWORK_OBJECT_CACHE_
