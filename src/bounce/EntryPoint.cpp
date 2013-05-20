/*
 * EntryPoint.cpp
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#include "EntryPoint.h"
#include "App.h"

namespace bounce {

EntryPoint::EntryPoint() {
	// TODO Auto-generated constructor stub

}

EntryPoint::~EntryPoint() {
	// TODO Auto-generated destructor stub
}

int EntryPoint::run(EventManager& eventManager, void (*flush)(void*), void* context) {
	bounce::App app(eventManager, flush, context);

	return app.onExecute();
}

} /* namespace bounce */
