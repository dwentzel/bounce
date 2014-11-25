#ifndef BOUNCE_FRAMEWORK_OBJECT_CACHE_
#define BOUNCE_FRAMEWORK_OBJECT_CACHE_

#include <vector>

namespace bounce {
        
    template<typename TObject>
    class ObjectCache {
    private:
        std::vector<TObject> cache_;
        
    public:
        typedef typename std::vector<TObject>::iterator iterator;
        typedef typename std::vector<TObject>::const_iterator const_iterator;
        
        
        ObjectCache();
        
        iterator begin();
        const_iterator begin() const;
        
        iterator end();
        const_iterator end() const;
        
        template<typename... FactoryArgs>
        unsigned int GenerateObject(FactoryArgs&&...);
        TObject& GetObject(unsigned int handle);
        
    };

    template<typename TObject>
    ObjectCache<TObject>::ObjectCache()
    {
        
    }
    
    template<typename TObject>
    typename ObjectCache<TObject>::iterator ObjectCache<TObject>::begin()
    {
        return cache_.begin();
    }
    
    template<typename TObject>
    typename ObjectCache<TObject>::const_iterator ObjectCache<TObject>::begin() const
    {
        return cache_.begin();
    }
    
    template<typename TObject>
    typename ObjectCache<TObject>::iterator ObjectCache<TObject>::end()
    {
        return cache_.end();
    }
    
    template<typename TObject>
    typename ObjectCache<TObject>::const_iterator ObjectCache<TObject>::end() const
    {
        return cache_.end();
    }
    
    template<typename TObject> template<typename... FactoryArgs>
    unsigned int ObjectCache<TObject>::GenerateObject(FactoryArgs&&... args)
    {
        unsigned int handle = cache_.size();
        
        cache_.push_back(TObject::Create(args...));
        
        return handle;
    }
    
    template<typename TObject>
    TObject& ObjectCache<TObject>::GetObject(unsigned int handle)
    {
        return cache_[handle];
    }
    
}

#endif // BOUNCE_FRAMEWORK_OBJECT_CACHE_
