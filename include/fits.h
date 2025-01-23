#ifndef __FITS_H__
#define __FITS_H__

#include "definitions.h"
#include "constants.h"
#include "keyword.h"
#include "unsorted_map.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace fits {
    
    class Fits {
        public:
            Fits();
            Fits(std::string filename_);

            void read(std::string filename);
            void write(std::string filename);
    };
}

#endif
