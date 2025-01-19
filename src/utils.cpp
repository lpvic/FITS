#include "utils.h"

std::string trimLeadingSpaces(const std::string str) {
    int pos = str.find_first_not_of(' ');
    return str.substr(pos);
}

std::string trimTrailingSpaces(const std::string str) {
    int pos = str.find_last_not_of(' ');
    if (pos == std::string::npos)
        return str;
    else
        return str.substr(0, pos + 1);
}

std::string trimSpaces(const std::string str) {
    if (str != "") {
        int startPos = str.find_first_not_of(' ');
        int endPos = str.find_last_not_of(' ');

        if ((startPos != std::string::npos) && (endPos != std::string::npos))
            return str.substr(startPos, endPos - startPos + 1);
        else
            return "";
    }
    else {
        return "";
    }
}
