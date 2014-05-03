/*
 * log.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef LOG_H_
#define LOG_H_

#ifdef NDEBUG
#define LOG(x) if (0) std::cerr
#else
#define LOG(logLevel) bounce::LogManager::getInstance().log(logLevel)
#endif
#define LOG_DEBUG LOG(bounce::LogLevel::Debug)

#include "Logger.hpp"
#include "LogManager.hpp"

#endif /* LOG_H_ */
