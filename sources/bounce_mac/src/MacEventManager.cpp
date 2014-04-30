/*
 * MacEventManager.cpp
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#include <iostream>
#include "MacEventManager.hpp"

namespace bounce_mac {

MacEventManager::MacEventManager() {
	eventQueue = new bounce::EventQueue();

}

MacEventManager::~MacEventManager() {
	delete eventQueue;
}

std::unique_ptr<bounce::Event> MacEventManager::pollEvent() {

	//std::cout << "poll" << std::endl;

	std::unique_ptr<bounce::Event> event;
	if (eventQueue->consume(event))
		return event;
	else
		return nullptr;
}

void MacEventManager::queueEvent(std::unique_ptr<bounce::Event> event) {
	eventQueue->produce(std::move(event));
}

} /* namespace bounce */
