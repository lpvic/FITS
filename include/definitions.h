#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <limits>

namespace fits {
    using size_type = std::size_t;
    using byte = char;

    static constexpr size_type npos = std::numeric_limits<size_type>::max();
}

#endif