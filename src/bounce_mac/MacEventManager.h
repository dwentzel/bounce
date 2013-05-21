/*
 * MacEventManager.h
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#ifndef MACEVENTMANAGER_H_
#define MACEVENTMANAGER_H_

#include "bounce/event/Event.h"

namespace bounce_mac {

class MacEventManager : public bounce::EventManager {
private:
	bounce::EventQueue* eventQueue;
public:
	MacEventManager();
	virtual ~MacEventManager();

	virtual bounce::Event* pollEvent();

	void queueEvent(bounce::Event* event);
};

} /* namespace bounce */
#endif /* MACEVENTMANAGER_H_ */
