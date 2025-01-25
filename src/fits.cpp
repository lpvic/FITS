#include "fits.h"

namespace fits {

    bool Fits::read(std::string filename) {
        size_type header_begin = 0;
        byte_type buffer[BLOCK_SIZE];
        size_type counter = 0;
        std::vector<block_type> blocks;
        std::vector<size_type> hdu_index;
        std::vector<std::pair<size_type, size_type>> header_index;

        std::fstream file(filename, std::ios_base::in | std::ios_base::binary);

        if (!file.is_open()) {
            std::cout << "File not opened" << std::endl;
            return false;
        }

        while ((file.read(buffer, BLOCK_SIZE)) || (file.gcount() > 0)) {
            blocks.emplace_back(buffer, buffer + file.gcount());

            if ((std::string_view(blocks.back().data(), 6) == "SIMPLE") || (std::string_view(blocks.back().data(), 8) == "XTENSION")) {
                hdu_index.push_back(counter);
                header_begin = counter;
            }

            if (std::string_view(blocks.back().data(), BLOCK_SIZE).find("END     ") != std::string_view::npos) {
                header_index.push_back(std::make_pair<>(header_begin, counter));
            }
            ++counter;
        }

        file.clear();
        file.seekg(0, std::ios_base::end);
        size_ = file.tellg();
        file.close();

        if (blocks.back().size() != BLOCK_SIZE) {
            blocks.back().insert(blocks.back().end(), BLOCK_SIZE - blocks.back().size(), '\0');
            size_ = blocks.size() * BLOCK_SIZE;
        }
        nblocks_ = size_ / BLOCK_SIZE;

        for (size_type i = 0; i < hdu_index.size(); ++i) {
            std::vector<block_type> h(blocks.begin() + header_index[i].first, blocks.begin() + header_index[i].second + 1);
            hdus_.push_back(Hdu(h, Data()));
        }

        return true;
    }
}
