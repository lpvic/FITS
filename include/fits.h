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
            void write(std::string filename);

        private:
            size_type size_ = npos;
            size_type nblocks_ = npos;
            std::vector<std::unique_ptr<byte[]>> blocks_;

            bool has_correct_size(size_type s_) { return !(s_ % BLOCK_SIZE); }
    };
}

#endif
