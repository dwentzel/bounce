/*
 * EntryPoint.cpp
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#include "EntryPoint.hpp"
#include "App.hpp"

namespace bounce {

EntryPoint::EntryPoint() {
	// TODO Auto-generated constructor stub

}

EntryPoint::~EntryPoint() {
	// TODO Auto-generated destructor stub
}

int EntryPoint::run(
		const ApplicationContext& applicationContext,
		EventManager& eventManager,
		void (*flush)(void*),
		void* context) {
	bounce::App app(eventManager, flush, context);

	return app.onExecute();
}

} /* namespace bounce */
