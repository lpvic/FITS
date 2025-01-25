#ifndef __HDU_H__
#define __HDU_H__

#include "unsorted_map.hpp"
#include "keyword.h"

#include <string>
#include<vector>

namespace fits {
    
    class Hdu {
        public:
            std::vector<com::unsorted_map<std::string, Keyword>> header;
            char* data;
            std::vector<int> naxis;
            int bitpix;
    };
}

#endif
