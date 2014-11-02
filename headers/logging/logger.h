#ifndef BOUNCE_LOGGER_H_
#define BOUNCE_LOGGER_H_

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

	virtual std::wostream& Log(const LogLevel& logLevel) = 0;
};


inline Logger::~Logger() {

}

}


#endif // BOUNCE_LOGGER_H_
