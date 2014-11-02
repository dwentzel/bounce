#ifndef DEFAULTLOGGER_H_
#define DEFAULTLOGGER_H_

#include <iostream>

namespace bounce {

class DefaultLogger : public Logger {
public:
	~DefaultLogger() {
		std::cout << "Default logger destroyed." << std::endl;
	}

	std::wostream& Log(const LogLevel& logLevel) {
		return std::wcout;
	}
};

}


#endif
