#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <limits>
#include <vector>

namespace fits {
    using size_type = unsigned long;
    using byte_type = char;
    using block_type = std::vector<byte_type>;
    using bitpix8_type = unsigned char;
    using bitpix16_type = unsigned short;
    using bitpix32_type = unsigned int;
    using bitpix64_type = unsigned long;
    using bitpix_32_type = float;
    using bitpoix_64_type = double;


    static constexpr size_type npos = std::numeric_limits<size_type>::max();
    static constexpr size_type BLOCK_SIZE = 2880;
    static constexpr size_type HEADER_LINE_SIZE = 80;
    static constexpr size_type KEYWORD_SIZE = 8; 
}

#endif