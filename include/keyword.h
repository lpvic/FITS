#ifndef __KEYWORD_H__
#define __KEYWORD_H__

#include "definitions.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace fits {

    class Keyword {      
        public:
            std::string keyword;
            std::string str_value;
            std::string comment;        

            Keyword() : keyword(""), str_value(""), comment("") {};
            Keyword(std::string keyword_, std::string str_value_, std::string comment_) : keyword(keyword_),
                                                                                          str_value(str_value_), 
                                                                                          comment(comment_) {};
            Keyword(const std::string line);
            Keyword(const char* buffer) : Keyword(std::string(buffer, HEADER_LINE_SIZE)) {};
            
            std::string str() const;

            friend std::ostream& operator<<(std::ostream& os, const Keyword& keyw);
    };
}

#endif
