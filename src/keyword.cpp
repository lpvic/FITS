#include "keyword.h"

#include "utils.h"
#include "constants.h"

Keyword::Keyword(const std::string line) {
    int commentStart;
    int slash = 1;
    keyword = trimSpaces(line.substr(0, 8));

    if (keyword == "END") {
        value = "";
        comment = "";
    }
    else {
        commentStart = line.find_first_of('/');
        if (commentStart != std::string::npos) {
            comment = line.substr(commentStart + 1);
        }
        else {
            comment = "";
            slash = 0;
        }

        value = line.substr(KEYWORD_SIZE, HEADER_LINE_SIZE - comment.size() - KEYWORD_SIZE - slash);
        if (value[0] == '=') {
            value = value.substr(2);
        }

        comment = trimSpaces(comment);
        value = trimSpaces(value);
    }
}
