/*
 * LogManager.cpp
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#include "logging/LogManager.h"

namespace bounce {

void LogManager::setLogger(Logger* logger) {
	this->logger = std::unique_ptr<Logger>(logger);
}

std::ostream& LogManager::log(const LogLevel& logLevel) {
	return logger->Log(logLevel);
}

} /* namespace bounce */
