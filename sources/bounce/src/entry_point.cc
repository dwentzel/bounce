/*
 * EntryPoint.cpp
 *
 *  Created on: 15 maj 2013
 *      Author: daniel
 */

#include "entry_point.h"
#include "app.h"

namespace bounce {

EntryPoint::EntryPoint() {
	// TODO Auto-generated constructor stub

}

EntryPoint::~EntryPoint() {
	// TODO Auto-generated destructor stub
}

int EntryPoint::run(const ApplicationContext& application_context) {
	bounce::App app(application_context);

	return app.onExecute();
}

} /* namespace bounce */
