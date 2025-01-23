#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>

namespace fits {
    
    class NonConformantFitsException : public std::exception {
        public:
            NonConformantFitsException(char* msg) : message_(msg) {}
            char* what() { return message_; }

        private:
            char* message_;
    };
}

#endif
