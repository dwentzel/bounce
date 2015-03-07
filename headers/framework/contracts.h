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

#define CONTRACT_REQUIRES(x) (assert(x))
#define ___MERGE(a, b) a##b
#define ___POST(line) ___MERGE(___bounce_postcondition, line)
#define ___UNIQUE_POSTCONDITION ___POST(__LINE__)
#define CONTRACT_ENSURES(x) \
    bounce::contracts::Postcondition ___UNIQUE_POSTCONDITION([&](){return x;});

#endif // BOUNCE_FRAMEWORK_CONTRACTS_H_
