#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <limits>

namespace fits {
    using size_type = std::size_t;
    using byte = char;

    static constexpr size_type npos = std::numeric_limits<size_type>::max();
    static constexpr int BLOCK_SIZE = 2880;
    static constexpr int HEADER_LINE_SIZE = 80;
    static constexpr int KEYWORD_SIZE = 8;
}

#endif