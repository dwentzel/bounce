/*
 * LockFreeQueue.h
 *
 *  Created on: 19 maj 2013
 *      Author: daniel
 */

#ifndef LOCKFREEQUEUE_H_
#define LOCKFREEQUEUE_H_

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

} /* namespace bounce */
#endif /* LOCKFREEQUEUE_H_ */
