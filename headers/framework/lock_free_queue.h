#ifndef BOUNCE_FRAMEWORK_LOCKFREEQUEUE_H_
#define BOUNCE_FRAMEWORK_LOCKFREEQUEUE_H_

#include <memory>
#include <atomic>

namespace bounce {
    
    template<class T>
    class LockFreeQueue {
    public:
        LockFreeQueue();
        ~LockFreeQueue();
        
        void Produce(const T& item);
        bool Consume(T& item);
        
    private:
        struct Node {
            Node(T val);
            
            T value;
            Node* next;
        };
        
        Node* first_;
        std::atomic<Node*> divider_;
        std::atomic<Node*> last_;
        
    };
    
    template<class T>
    LockFreeQueue<T>::Node::Node(T val)
    : value(val), next(nullptr)
    {
        
    }
    
    template<class T>
    LockFreeQueue<T>::LockFreeQueue()
    : first_(new Node(T())), divider_(first_), last_(first_)
    {
        
    }
    
    template<class T>
    LockFreeQueue<T>::~LockFreeQueue()
    {
        while (first_ != nullptr) {
            Node* tmp = first_;
            first_ = tmp->next;
            delete tmp;
        }
    }
    
    template<typename T>
    void LockFreeQueue<T>::Produce(const T& item)
    {
        Node* new_node = new Node(item);
        last_.load()->next = new_node;
        last_ = new_node;
        
        while (first_ != divider_) {
            Node* tmp = first_;
            first_ = first_->next;
            delete tmp;
        }
    }
    
    template<typename T>
    bool LockFreeQueue<T>::Consume(T& item)
    {
        Node* divider_node = divider_.load();
        
        if (divider_node != last_) {
            item = divider_node->next->value;
            divider_.store(divider_node->next);
            return true;
        }
        
        return false;
    }
    
    
    
    template<class T>
    class LockFreeQueue<std::unique_ptr<T>> {
    public:
        LockFreeQueue();
        ~LockFreeQueue();
        
        void Produce(std::unique_ptr<T> item);
        bool Consume(std::unique_ptr<T>& item);
        
    private:
        struct Node {
            Node();
            Node(std::unique_ptr<T> val);
            
            std::unique_ptr<T> value;
            Node* next;
        };
        
        Node* first_;
        std::atomic<Node*> divider_;
        std::atomic<Node*> last_;
        
    };
    
    template<class T>
    LockFreeQueue<std::unique_ptr<T>>::Node::Node()
    : value(std::unique_ptr<T>(nullptr)), next(nullptr)
    {
        
    }

    template<class T>
    LockFreeQueue<std::unique_ptr<T>>::Node::Node(std::unique_ptr<T> val)
    : value(std::move(val)), next(nullptr)
    {
        
    }
    
    template<class T>
    LockFreeQueue<std::unique_ptr<T>>::LockFreeQueue()
    : first_(new Node()), divider_(first_), last_(first_)
    {
        
    }
    
    template<class T>
    LockFreeQueue<std::unique_ptr<T>>::~LockFreeQueue()
    {
        while (first_ != nullptr) {
            Node* tmp = first_;
            first_ = tmp->next;
            delete tmp;
        }
    }
    
    template<class T>
    void LockFreeQueue<std::unique_ptr<T>>::Produce(std::unique_ptr<T> item)
    {
        Node* newNode = new Node(std::move(item));
        last_.load()->next = newNode;
        last_ = newNode;
        
        while (first_ != divider_) {
            Node* tmp = first_;
            first_ = first_->next;
            delete tmp;
        }
    }
    
    template<class T>
    bool LockFreeQueue<std::unique_ptr<T>>::Consume(std::unique_ptr<T>& item)
    {
        Node* dividerNode = divider_.load();
        
        if (dividerNode != last_) {
            item = std::move(dividerNode->next->value);
            divider_.store(dividerNode->next);
            return true;
        }
        
        return false;
    }
}

#endif // BOUNCE_FRAMEWORK_LOCKFREEQUEUE_H_
