/*
 * MacEventManager.cpp
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#include "MacEventManager.h"

namespace bounce_mac {

MacEventManager::MacEventManager() {
	// TODO Auto-generated constructor stub

}

MacEventManager::~MacEventManager() {
	// TODO Auto-generated destructor stub
}

bounce::Event* MacEventManager::pollEvent() {

	bounce::Event* event;
	if (eventQueue.consume(event))

		return event;
	else
		return 0;
}

void MacEventManager::queueEvent(bounce::Event* event) {
	eventQueue.produce(event);
}

} /* namespace bounce */
