#ifndef BOUNCE_IMPORTER_EXCEPTIONS_H_
#define BOUNCE_IMPORTER_EXCEPTIONS_H_

#include "framework/exceptions.h"

namespace bounce {

    class ImporterException : public BounceException {
    private:
    	ImporterException& operator=(const ImporterException&) = delete;

    public:
    	ImporterException();
    	ImporterException(const ImporterException& other);
    	virtual ~ImporterException();
    };

}

#endif // BOUNCE_IMPORTER_EXCEPTIONS_H_
