#include "fits.h"

namespace fits {

    bool Fits::read(std::string filename) {
        size_type header_begin = 0;
        byte_type buffer[BLOCK_SIZE];
        size_type counter = 0;
        std::fstream file(filename, std::ios_base::in | std::ios_base::binary);

        if (!file.is_open()) {
            std::cout << "File not opened" << std::endl;
            return false;
        }

        while ((file.read(buffer, BLOCK_SIZE)) || (file.gcount() > 0)) {
            blocks_.emplace_back(buffer, buffer + file.gcount());

            if ((std::string_view(blocks_.back().data(), 6) == "SIMPLE") || (std::string_view(blocks_.back().data(), 8) == "XTENSION")) {
                hdu_index.push_back(counter);
                header_begin = counter;
            }

            if (std::string_view(blocks_.back().data(), BLOCK_SIZE).find("END     ") != std::string_view::npos) {
                header_index.push_back(std::make_pair<>(header_begin, counter));
            }
            ++counter;
        }

        file.clear();
        file.seekg(0, std::ios_base::end);
        size_ = file.tellg();
        if (blocks_.back().size() != BLOCK_SIZE) {
            blocks_.back().insert(blocks_.back().end(), BLOCK_SIZE - blocks_.back().size(), '\0');
            size_ = blocks_.size() * BLOCK_SIZE;
        }
        nblocks_ = size_ / BLOCK_SIZE;

        file.close();

        return true;
    }
}
