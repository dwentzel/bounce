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

int EntryPoint::run(const EventManager& eventManager) {
	bounce::App app(eventManager);

	return app.onExecute();
}

} /* namespace bounce */
