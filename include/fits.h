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
    private:        
        void getHeaderBlockPosition();

    public:
        int size;
        int nblocks;

        std::vector<int> headerStartBlock;
        std::vector<int> dataStartBlock;
        std::vector<int> headerEndBlock;
        std::vector<int> dataEndBlock;

        std::map<int, unsorted_map<std::string, Keyword>> headers;
  
        explicit Fits(const char* filename, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::binary);
        explicit Fits(const std::string& filename, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::binary);

        void readBlock(char* buffer, const int n = 0);
        void readBlock(char* buffer, const int from, const int to);
        void readHeader();
        void readHeader(int n);

        using std::fstream::close;
        using std::fstream::is_open;
        using std::fstream::seekg;
        using std::fstream::tellg;
        using std::fstream::read;
        using std::fstream::clear;
};

#endif
