#include <iostream>
#include <string>

#include "definitions.h"
#include "utils.h"
#include "fits.h"
#include "hdu.h"

int main(void) {
    fits::Fits fits_file("../../../short_2024.12.07_IC434_v1.0.fit");

    std::cout << "File size: " << fits_file.size() << std::endl;
    std::cout << "Number of blocks: " << fits_file.nblocks() << std::endl;
    
    fits::Hdu hdu = fits_file.get_hdu(0);
    std::cout << hdu.header.size() << std::endl;

    hdu.header.to_blocks();
    
    return 0;
}
