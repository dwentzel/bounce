/*
 * EntryPoint.h
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_ENTRYPOINT_H_
#define BOUNCE_ENTRYPOINT_H_

#include "application_context.h"
#include "event.h"

namespace bounce {

class EntryPoint {
public:
	EntryPoint();
	virtual ~EntryPoint();

	int run(const ApplicationContext& applicationContext);
};

} /* namespace bounce */
#endif // BOUNCE_ENTRYPOINT_H_
