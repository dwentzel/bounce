/*
 * EntryPoint.h
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#ifndef ENTRYPOINT_H_
#define ENTRYPOINT_H_

#include "Event.h"

namespace bounce {

class EntryPoint {
public:
	EntryPoint();
	virtual ~EntryPoint();

	int run(const EventManager& eventManager, void (*flush)(void*), void* context);
};

} /* namespace bounce */
#endif /* ENTRYPOINT_H_ */
