#ifndef __FITS_H__
#define __FITS_H__

#include "definitions.h"
#include "keyword.h"
#include "hdu.h"
#include "unsorted_map.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <string_view>

namespace fits {
    
    class Fits {
        public:
            Fits(std::string filename) { read(filename); }

            bool read(std::string filename);
            bool write(std::string filename);
            size_type size() { return size_; }
            size_type nblocks() { return nblocks_; }

//        private:
            size_type size_ = npos;
            size_type nblocks_ = npos;
            std::vector<size_type> hdu_index;
            std::vector<std::pair<size_type, size_type>> header_index;
            std::vector<block_type> blocks_;

            bool has_correct_size(size_type s_) { return !(s_ % BLOCK_SIZE); }
    };
}

#endif
