/*
 * ApplicationContext.h
 *
 *  Created on: 26 apr 2014
 *      Author: daniel
 */

#ifndef BOUNCE_APPLICATIONCONTEXT_H_
#define BOUNCE_APPLICATIONCONTEXT_H_

#include <string>
#include <memory>
#include "event.h"

namespace bounce {

class ApplicationContext {
public:
    ApplicationContext(
        void(*flush)(void*),
        void* context) : flush_(flush), context_(context) 
    {}

    ~ApplicationContext() {}

    EventManager* event_manager_ptr() { return &event_manager_; }
    const EventManager& event_manager() const { return event_manager_; }

    void flush() const { flush_(context_); }

private:
    EventManager event_manager_;
    void(*flush_)(void*);
    void* context_;
};

}


#endif /* APPLICATIONCONTEXT_H_ */
