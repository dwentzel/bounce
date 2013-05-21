/*
 * MacEventManager.cpp
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#include <iostream>
#include "MacEventManager.h"

namespace bounce_mac {

MacEventManager::MacEventManager() {
	eventQueue = new bounce::EventQueue();

}

MacEventManager::~MacEventManager() {
	delete eventQueue;
}

bounce::Event* MacEventManager::pollEvent() {

	//std::cout << "poll" << std::endl;

	bounce::Event* event;
	if (eventQueue->consume(event))
		return event;
	else
		return 0;
}

void MacEventManager::queueEvent(bounce::Event* event) {
	eventQueue->produce(event);
}

} /* namespace bounce */
