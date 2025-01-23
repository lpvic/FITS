#include "fits.h"
#include "hdu.h"

namespace fits {
    Fits::Fits(std::string filename_) {

    }

    void Fits::read(std::string filename) {
        std::fstream f(filename, std::ios_base::in | std::ios_base::binary);
    }
}
