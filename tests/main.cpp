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
    
    fits::Hdu& hdu = fits_file.get_hdu(0);
    std::cout << hdu.header.size() << std::endl;

    auto bl = hdu.header.to_blocks();
    std::cout << bl.size() << std::endl;

    for (auto elem : bl) {
        std::cout << elem.size() << std::endl;
    }

    std::cout << hdu.header.get("NAXIS").first->second.str_value << std::endl;
    hdu.header.get("NAXIS").first->second.str_value = "0";
    std::cout << hdu.header.get("NAXIS").first->second.str_value << std::endl;
    hdu.header.get("NAXIS1").first->second.str_value = "0";
    hdu.header.erase("NAXIS1");
    hdu.header.erase("NAXIS2");
    hdu.header.erase("NAXIS3");

    std::cout << fits_file.get_hdu(0).header.size() << std::endl;

    fits_file.write("../../../test.fit");
    return 0;
}
