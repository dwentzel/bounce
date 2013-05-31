/*
 * LogManager.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include "Logger.h"

namespace bounce {

class LogManager {
private:
	LogManager() : logger(nullptr) {};
    LogManager(const LogManager&);
	//virtual ~LogManager() = 0;

    void operator=(const LogManager&);

    Logger* logger;
public:
    static LogManager& getInstance() {
    	static LogManager instance;
    	return instance;
    }

	void setLogger(Logger* logger);
	std::ostream& log(const LogLevel& logLevel);
};



} /* namespace bounce */
#endif /* LOGMANAGER_H_ */
