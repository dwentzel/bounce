#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>

namespace bounce {

enum LogLevel {
	Debug,
	Info,
	Warning,
	Error
};


class Logger {
private:
protected:

public:
	virtual ~Logger() = 0;

	virtual std::ostream& Log(const LogLevel& logLevel) = 0;
};


inline Logger::~Logger() {

}

}


#endif
