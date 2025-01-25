#ifndef __KEYWORD_H__
#define __KEYWORD_H__

#include "definitions.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace fits {

    class Keyword {      
        public:
            std::string keyword;
            std::string str_value;
            std::string comment;        

            Keyword() {};
            Keyword(const std::string line);
            Keyword(const char* buffer) : Keyword(std::string(buffer, HEADER_LINE_SIZE)) {};

            friend std::ostream& operator<<(std::ostream& os, const Keyword& keyw);
    };
}

#endif
