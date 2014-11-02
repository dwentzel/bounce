/*
 * LogManager.cpp
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#include "logging/log_manager.h"

namespace bounce {

void LogManager::set_logger(Logger* logger) {
	logger_ = std::unique_ptr<Logger>(logger);
}


std::wostream& LogManager::Log(const LogLevel& log_level) {
	return logger_->Log(log_level);
}

} /* namespace bounce */
