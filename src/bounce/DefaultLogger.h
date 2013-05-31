#ifndef DEFAULTLOGGER_H_
#define DEFAULTLOGGER_H_

namespace bounce {

class DefaultLogger : public Logger {
public:
	std::ostream& Log(const LogLevel& logLevel) {
		return std::cout;
	}
};

}


#endif
