#ifndef __KEYWORD_H__
#define __KEYWORD_H__

#include <string>
#include "constants.h"

class Keyword {      
    public:
        std::string keyword;
        std::string value;       
        std::string comment;        

        Keyword() {};
        Keyword(const std::string line);
        Keyword(const char* buffer) : Keyword(std::string(buffer, HEADER_LINE_SIZE)) {};
};

#endif
