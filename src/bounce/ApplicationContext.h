/*
 * ApplicationContext.h
 *
 *  Created on: 26 apr 2014
 *      Author: daniel
 */

#ifndef APPLICATIONCONTEXT_H_
#define APPLICATIONCONTEXT_H_

#include <string>

namespace bounce {

class ApplicationContext {
private:
	std::string binaryPath;

public:
	ApplicationContext();

	const std::string& getBinaryPath() const;
	void setBinaryPath(const std::string& binaryPath);
};

}


#endif /* APPLICATIONCONTEXT_H_ */
