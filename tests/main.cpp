#include <iostream>
#include <string>

#include "definitions.h"
#include "fits.h"
#include "utils.h"

int main(void) {
    fits::Fits fits_file("../../../2024.12.07_IC434_v1.0.fit");

    std::cout << "File size: " << fits_file.size_ << std::endl;
    std::cout << "Number of blocks: " << fits_file.nblocks_ << std::endl;
    std::cout << "Number of blocks read: " << fits_file.blocks_.size() << std::endl;
    std::cout << "Size of first block: " << fits_file.blocks_.front().size() << std::endl;
    std::cout << "Size of last block: " << fits_file.blocks_.back().size() << std::endl;
    std::cout << "Size of block 8976: " << fits_file.blocks_[8976].size() << std::endl;
    std::cout << "Number of HDUs: " << fits_file.hdu_index.size() << std::endl;
    std::cout << "Index of HDU: " << fits_file.hdu_index[0].first << " " << fits_file.hdu_index[0].second << std::endl;

    return 0;
}
