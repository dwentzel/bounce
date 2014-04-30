/*
 * MacEventManager.h
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#ifndef MACEVENTMANAGER_H_
#define MACEVENTMANAGER_H_

#include <memory>
#include "bounce/Event.h"

namespace bounce_mac {

class MacEventManager : public bounce::EventManager {
private:
	bounce::EventQueue* eventQueue;
public:
	MacEventManager();
	virtual ~MacEventManager();

	virtual std::unique_ptr<bounce::Event> pollEvent();

	void queueEvent(std::unique_ptr<bounce::Event> event);
};

} /* namespace bounce */
#endif /* MACEVENTMANAGER_H_ */
