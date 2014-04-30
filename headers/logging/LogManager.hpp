/*
 * LogManager.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include <memory>
#include "Logger.hpp"

namespace bounce {

class LogManager {
private:
	LogManager() : logger(nullptr) {};
    LogManager(const LogManager&);
	~LogManager();

    void operator=(const LogManager&);

    std::unique_ptr<Logger> logger;
public:
    static LogManager& getInstance() {
    	static LogManager instance;
    	return instance;
    }

	void setLogger(Logger* logger);
	std::ostream& log(const LogLevel& logLevel);
};


inline LogManager::~LogManager() {
	//delete logger;
}


} /* namespace bounce */
#endif /* LOGMANAGER_H_ */
