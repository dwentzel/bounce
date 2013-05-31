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
#define LOG(logLevel) LogManager::getInstance().log(logLevel)
#endif

#include "Logger.h"
#include "LogManager.h"

#endif /* LOG_H_ */
