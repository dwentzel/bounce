/*
 * MacEventManager.h
 *
 *  Created on: 16 maj 2013
 *      Author: daniel
 */

#ifndef MACEVENTMANAGER_H_
#define MACEVENTMANAGER_H_

#include "bounce/Event.h"

namespace bounce_mac {

class MacEventManager : public bounce::EventManager {
public:
	MacEventManager();
	virtual ~MacEventManager();

	virtual bounce::Event* pollEvent() const;
};

} /* namespace bounce */
#endif /* MACEVENTMANAGER_H_ */
