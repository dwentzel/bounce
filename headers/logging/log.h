/*
 * log.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_LOG_H_
#define BOUNCE_LOG_H_

//#ifdef NDEBUG
//#define LOG(x) if (0) std::cerr
//#else
#define LOG(log_level) \
if (log_level > bounce::LogManager::instance().max_log_level()) ; \
else bounce::LogSync(bounce::LogManager::instance().Log(log_level))
//#endif

#define LOG_ERROR LOG(bounce::LOG_LEVEL_ERROR)
#define LOG_WARNING LOG(bounce::LOG_LEVEL_WARNING)
#define LOG_INFO LOG(bounce::LOG_LEVEL_INFO)
#define LOG_DEBUG LOG(bounce::LOG_LEVEL_DEBUG)

#include <ostream>

namespace bounce {
    
    enum LogLevel {
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG
    };
    
    std::wostream& operator<<(std::wostream& out, const std::string& str);    
}

#include "log_sync.h"
#include "log_manager.h"

#endif /* LOG_H_ */
