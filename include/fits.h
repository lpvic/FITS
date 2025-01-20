#ifndef __FITS_H__
#define __FITS_H__

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "constants.h"
#include "keyword.h"
#include "unsorted_map.hpp"

class Fits : private std::fstream {
    public:
        using std::fstream::close;
        using std::fstream::is_open;
        using std::fstream::seekg;
        using std::fstream::tellg;
        using std::fstream::read;
        using std::fstream::clear;

        int size;
        int nblocks;

        std::vector<int> header_start_block;
        std::vector<int> data_start_block;
        std::vector<int> header_end_block;
        std::vector<int> data_end_block;

        std::vector<std::pair<size_t, size_t>> header_blocks_pos;
        std::vector<std::pair<size_t, size_t>> data_blocks_pos;


        std::map<int, unsorted_map<std::string, Keyword>> headers;
  
        explicit Fits(const char* filename, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::binary);
        explicit Fits(const std::string& filename, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::binary);

        void read_block(char* buffer, const int n = 0);
        void read_block(char* buffer, const int from, const int to);
        void read_header();
        void read_header(int n);

    private:        
        void get_header_block_pos();        
};

#endif
