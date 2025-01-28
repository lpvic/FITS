#ifndef __HEADER_H__
#define __HEADER_H__

#include "definitions.h"
#include "vectormap.hpp"
#include "keyword.h"

#include <ranges>
#include <sstream>
#include <iomanip>

namespace fits {
    class Header : public com::vectormap<std::string, Keyword> {
        public:
            Header() {};
            Header(const std::vector<block_type>& blocks);

            std::vector<block_type> to_blocks();
    };
}
#endif