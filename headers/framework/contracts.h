#ifndef BOUNCE_FRAMEWORK_CONTRACTS_H_
#define BOUNCE_FRAMEWORK_CONTRACTS_H_

#include <cassert>
#include <functional>

namespace bounce {
    namespace contracts {
        
        class Postcondition {
        public:
            Postcondition(std::function<bool ()> postcondition)
            : postcondition_(postcondition)
            {
                
            }
            
            ~Postcondition()
            {
                assert(postcondition_());
            }
        private:
            std::function<bool ()> postcondition_;
            
            Postcondition(const Postcondition&) = delete;
            Postcondition& operator=(const Postcondition&) = delete;
        };
    }
    
}

#define REQUIRES(x) (assert(x))
#define MERGE(a, b) a##b
#define POST(line) MERGE(___bounce_postcondition, line)
#define UNIQUE_POSTCONDITION POST(__LINE__)
#define ENSURES(x) \
    bounce::contracts::Postcondition UNIQUE_POSTCONDITION([&](){return x;});

#endif // BOUNCE_FRAMEWORK_CONTRACTS_H_
