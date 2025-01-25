#include "fits.h"

namespace fits {

    bool Fits::read(std::string filename) {
        size_type hdu_begin = 0;
        byte_type buffer[BLOCK_SIZE];
        size_type counter = 0;
        std::fstream file(filename, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);

        if (!file.is_open()) {
            std::cout << "File not opened" << std::endl;
            return false;
        }

        size_ = file.tellg();
        if (!has_correct_size(size_)) {
            std::cout << "Incorrect Size" << std::endl;
            return false;
        }
        nblocks_ = size_ / BLOCK_SIZE;
        
        file.clear();
        file.seekg(0, std::ios_base::beg);

        while ((file.read(buffer, BLOCK_SIZE)) || (file.gcount() > 0)) {
            blocks_.emplace_back(buffer, buffer + file.gcount());

            if ((std::string_view(blocks_.back().data(), 6) == "SIMPLE") || (std::string_view(blocks_.back().data(), 8) == "XTENSION")) {
                hdu_begin = counter;
            }

            if (std::string_view(blocks_.back().data(), BLOCK_SIZE).find("END     ") != std::string_view::npos) {
                hdu_index.push_back(std::make_pair<>(hdu_begin, counter));
            }
            ++counter;
        }

        file.close();

        return true;
    }
}
