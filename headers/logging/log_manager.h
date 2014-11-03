/*
 * LogManager.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_LOGMANAGER_H_
#define BOUNCE_LOGMANAGER_H_

#include <memory>
#include <vector>
#include "log.h"
#include "log_stream.h"

namespace bounce {
    
    class LogManager {
    private:
        LogManager();
        
        LogManager(const LogManager&) = delete;
        ~LogManager();
        
        void operator=(const LogManager&);
        
        LogStream log_stream_;
        
        LogLevel max_log_level_;
        
    public:
        static LogManager& instance() {
            static LogManager instance;
            return instance;
        }
        
        LogLevel max_log_level() const
        {
            return max_log_level_;
        }
        
        void max_log_level(LogLevel log_level)
        {
            max_log_level_ = log_level;
        }
        
        void set_logger(Logger* logger);
        
        std::wostream& Log(const LogLevel& log_level)
        {
            //            log_stream_ << log_level;
            
            return log_stream_;
        }
    };
    
}
#endif // BOUNCE_LOGMANAGER_H_
