#ifndef __HDU_H__
#define __HDU_H__

#include "header.h"
#include "data.h"

#include <string>
#include<vector>

namespace fits {
    
    class Hdu {
        public:
            Header header;
            Data data;

            Hdu() {};
            Hdu(Header header_, Data data_) : header(header_), data(data_) {};

            std::vector<block_type>& to_blocks();
    };
}

#endif
