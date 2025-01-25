#ifndef __HEADER_H__
#define __HEADER_H__

#include "definitions.h"
#include "unsorted_map.hpp"
#include "keyword.h"

namespace fits {
    class Header : public com::unsorted_map<std::string, Keyword> {
        public:
            Header(const std::vector<block_type>& blocks);

            std::vector<block_type>& to_blocks();
    };
}
#endif