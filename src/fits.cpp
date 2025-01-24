#include "fits.h"
#include "hdu.h"

namespace fits {

    bool Fits::read(std::string filename) {
        std::vector<int> hdu_begin;
        byte buffer[BLOCK_SIZE];
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
        
        file.seekg(0, std::ios_base::beg);
        std::cout << "start pos: " << file.tellg() << std::endl;
        int c = 0;
        do {
            file.read(buffer, BLOCK_SIZE);
            std::unique_ptr<byte[]> block = std::make_unique<byte[]>(BLOCK_SIZE);
            std::copy(buffer, buffer + BLOCK_SIZE, block.get());

            if ((std::string_view(block.get(), 6) == "SIMPLE") || (std::string_view(block.get(), 8) == "XTENSION")) {
                hdu_begin.push_back(c);
            }

            if (std::string_view(block.get(), BLOCK_SIZE).find("END     ") != std::string_view::npos) {
                std::cout << "END encontrado en bloque: " << c << std::endl;
            }

            blocks_.push_back(std::move(block));            
            c++;
        } 
        while(!file.eof());

        file.close();

        return true;
    }
}
