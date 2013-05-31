/*
 * LogManager.cpp
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#include "LogManager.h"

namespace bounce {

void LogManager::setLogger(Logger* logger) {
	this->logger = logger;
}

std::ostream& LogManager::log(const LogLevel& logLevel) {
	return logger->Log(logLevel);
}

} /* namespace bounce */
