/*
 * LockFreeQueue.h
 *
 *  Created on: 19 maj 2013
 *      Author: daniel
 */

#ifndef LOCKFREEQUEUE_H_
#define LOCKFREEQUEUE_H_

#include <atomic>

namespace bounce {

template <typename T>
class LockFreeQueue {
private:
	struct Node {
		Node(T val) : value(val), next(nullptr) {}
		T value;
		Node* next;
	};
	Node* first;
	std::atomic<Node*> divider;
	std::atomic<Node*> last;

public:
	LockFreeQueue() {
		first = divider = last =
				new Node(T());
	}

	~LockFreeQueue() {
		while (first != nullptr) {
			Node* tmp = first;
			first = tmp->next;
			delete tmp;
		}
	}

	void produce(const T& item) {
		Node* newNode = new Node(item);
		last.load()->next = newNode;
		last.store(newNode);

		while (first != divider) {
			Node* tmp = first;
			first = first->next;
			delete tmp;
		}
	}

	bool consume(T& item) {
		Node* dividerNode = divider.load();

		if (dividerNode != last.load()) {
			item = dividerNode->next->value;
			divider.store(dividerNode->next);
			return true;
		}
		return false;
	}
};

} /* namespace bounce */
#endif /* LOCKFREEQUEUE_H_ */
