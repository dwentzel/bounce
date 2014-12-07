#ifndef LOCKFREEQUEUE_H_
#define LOCKFREEQUEUE_H_

#include <memory>
#include <atomic>
#include <iostream>

namespace bounce {
    
    template<typename T>
    class LockFreeQueue {
    private:
        struct Node {
            Node(T val) :
            value(val), next(nullptr) {
            }
            T value;
            Node* next;
        };
        
        Node* first;
        std::atomic<Node*> divider;
        std::atomic<Node*> last;
        
    public:
        LockFreeQueue() {
            first = new Node(T());
            last = first;
            divider = first;
        }
        
        ~LockFreeQueue() {
            while (first != nullptr) {
                Node* tmp = first;
                first = tmp->next;
                delete tmp;
            }
        }
        
        LockFreeQueue(LockFreeQueue&& queue) {}
        
        void produce(const T& item);
        bool consume(T& item);
    };
    
    template<typename T>
    void LockFreeQueue<T>::produce(const T& item) {
        //std::cout << "produce" << std::endl;
        
        Node* newNode = new Node(item);
        last.load()->next = newNode;
        last = newNode;
        
        while (first != divider) {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }
    
    template<typename T>
    bool LockFreeQueue<T>::consume(T& item) {
        Node* dividerNode = divider.load();
        
        if (dividerNode != last) {
            item = dividerNode->next->value;
            divider.store(dividerNode->next);
            return true;
        }
        
        return false;
    }
    
    
    
    template<typename T>
    class LockFreeQueue<std::unique_ptr<T>> {
    private:
        struct Node {
            Node() : value(std::unique_ptr<T>(nullptr)), next(nullptr) {}
            
            Node(std::unique_ptr<T> val) :
            value(std::move(val)), next(nullptr) {
            }
            
            std::unique_ptr<T> value;
            Node* next;
        };
        
        Node* first;
        std::atomic<Node*> divider;
        std::atomic<Node*> last;
        
    public:
        LockFreeQueue() {
            first = new Node();
            last = first;
            divider = first;
        }
        
        ~LockFreeQueue() {
            while (first != nullptr) {
                Node* tmp = first;
                first = tmp->next;
                delete tmp;
            }
        }
        void produce(std::unique_ptr<T> item);
        bool consume(std::unique_ptr<T>& item);
    };
    
    
    template<typename T>
    void LockFreeQueue<std::unique_ptr<T>>::produce(std::unique_ptr<T> item) {
        Node* newNode = new Node(std::move(item));
        last.load()->next = newNode;
        last = newNode;
        
        while (first != divider) {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }
    
    template<typename T>
    bool LockFreeQueue<std::unique_ptr<T>>::consume(std::unique_ptr<T>& item) {
        Node* dividerNode = divider.load();
        
        if (dividerNode != last) {
            item = std::move(dividerNode->next->value);
            divider.store(dividerNode->next);
            return true;
        }
        
        return false;
    }
    
} /* namespace bounce */
#endif /* LOCKFREEQUEUE_H_ */
