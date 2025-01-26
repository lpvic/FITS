#include "keyword.h"

namespace fits {

    Keyword::Keyword(const std::string line) {
        int commentStart;
        int slash = 1;
        keyword = trim_spcs(line.substr(0, 8));

        if (keyword == "END") {
            str_value = "";
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

            str_value = line.substr(KEYWORD_SIZE, HEADER_LINE_SIZE - comment.size() - KEYWORD_SIZE - slash);
            if (str_value[0] == '=') {
                str_value = str_value.substr(2);
            }

            comment = trim_spcs(comment);
            str_value = trim_spcs(str_value);

            if ((keyword == "COMMENT") || (keyword == "HISTORY")) {
                comment = str_value;
                str_value = "";
            }
        }
    }

    std::string Keyword::str() const {
        std::string temp = keyword;

        if (temp.size() < KEYWORD_SIZE) {
            temp.insert(temp.size(),KEYWORD_SIZE - temp.size(),' ');
        }
        if ((str_value != "") && (comment != "")) {
            temp += "= " + str_value + " / " + comment;
        }
        else if (comment != "") {
            temp += comment;
        }
        else {
            temp += "= " + str_value;
        }
        return temp;       
    }

    std::ostream& operator<<(std::ostream& os, const Keyword& keyw) {
        os << keyw.str();
        return os;
    }
}
