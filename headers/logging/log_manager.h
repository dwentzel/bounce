/*
 * LogManager.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_LOGMANAGER_H_
#define BOUNCE_LOGMANAGER_H_

#include <memory>
#include "logger.h"

namespace bounce {

class LogManager {
private:
	LogManager() : logger_(nullptr) {};
    LogManager(const LogManager&) = delete;
	~LogManager();

    void operator=(const LogManager&);

    std::unique_ptr<Logger> logger_;

public:
    static LogManager& instance() {
    	static LogManager instance;
    	return instance;
    }

	void set_logger(Logger* logger);
	
    std::wostream& Log(const LogLevel& log_level);
};


inline LogManager::~LogManager() {
	//delete logger;
}

}
#endif // BOUNCE_LOGMANAGER_H_
