#include "keyword.h"

#include "utils.h"

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

    std::ostream& operator<<(std::ostream& os, const Keyword& keyw) {
        os << std::setw(8) << std::left << keyw.keyword << " ";
        if ((keyw.str_value != "") && (keyw.comment != "")) {
            os << keyw.str_value << " / " << keyw.comment;
        }
        else if (keyw.comment != "") {
            os << keyw.comment;
        }
        else {
            os << keyw.str_value;
        }

        return os;
    }
}
