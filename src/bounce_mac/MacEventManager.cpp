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

std::unique_ptr<bounce::Event> MacEventManager::pollEvent() {

	bounce::Event* event;
	if (eventQueue->consume(event))
		return std::unique_ptr<bounce::Event>(event);
	else
		return nullptr;
}

void MacEventManager::queueEvent(bounce::Event* event) {
	eventQueue->produce(event);
}

} /* namespace bounce */
