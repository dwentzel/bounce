/*
 * log.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_LOG_H_
#define BOUNCE_LOG_H_

#ifdef NDEBUG
#define LOG(x) if (0) std::cerr
#else
#define LOG(log_level) bounce::LogManager::instance().Log(log_level)
#endif
#define LOG_DEBUG LOG(bounce::LogLevel::Debug)


#include "logger.h"
#include "log_manager.h"

#endif /* LOG_H_ */
