#ifndef __FITS_H__
#define __FITS_H__

#include "definitions.h"
#include "keyword.h"
#include "header.h"
#include "data.h"
#include "hdu.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <string_view>
#include <ranges>

namespace fits {
    
    class Fits {
        public:
            std::vector<size_type> hdu_index;
            std::vector<std::pair<size_type, size_type>> header_index;

            Fits(std::string filename) { read(filename); }

            bool read(std::string filename);
            bool write(std::string filename);
            size_type size() { return size_; }
            size_type nblocks() { return nblocks_; }
            std::vector<block_type> blocks() { return blocks_; }
            std::vector<block_type> get_hdu(size_type n) { return blocks_; }

        private:
            size_type size_ = npos;
            size_type nblocks_ = npos;            
            std::vector<block_type> blocks_;
    };
}

#endif
