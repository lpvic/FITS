#include "fits.h"
#include "utils.h"

#include <iostream>

Fits::Fits(const char* filename, ios_base::openmode mode) : std::fstream(filename, mode) {
    get_header_block_pos();
}

Fits::Fits(const std::string& filename, ios_base::openmode mode) : std::fstream(filename, mode) {
    get_header_block_pos();
}

void Fits::read_block(char* buffer, const int n) {
    int counter = 0;

    clear();
    seekg(0, std::ios::beg);

    do {
        read(buffer, BLOCK_SIZE);
        counter++;
    } while (n >= counter);
}

void Fits::read_block(char* buffer, const int from, const int to) {
    int counter = 0;

    clear();
    seekg(0, std::ios::beg);
    int bytesToRead = (to - from + 1) * BLOCK_SIZE;
    char* tmp;

    // go to first block beginning
    read(tmp, from * BLOCK_SIZE);
    
    // read the blocks
    if (to < nblocks)
        read(buffer, bytesToRead);
    else
        read(buffer, (nblocks - from) * BLOCK_SIZE);
}

void Fits::read_header() {
    for (int i = 0; i < header_start_block.size(); i++) {
        read_header(i);
    }
}

void Fits::read_header(int n) {
    int startBlock = header_start_block[n];
    int endBlock = header_end_block[n];
    int bytesToRead = (endBlock - startBlock + 1) * BLOCK_SIZE;

    char *blocks = new char[bytesToRead];
    read_block(blocks, startBlock, endBlock);

    unsorted_map<std::string, Keyword> keywords;
    int counter = 0;
    for (int i = 0; i < bytesToRead; i += HEADER_LINE_SIZE) {
        char (&view)[HEADER_LINE_SIZE] = (char (&)[HEADER_LINE_SIZE])(*(blocks + i));
        std::string line(view, HEADER_LINE_SIZE);
        
        if (trim_spcs(line) == "")
            continue;

        Keyword k(line);
        keywords.push_back(std::make_pair<>(k.keyword, k));
        counter++;
    }

    headers.insert({n, keywords});

    delete [] blocks;
}

void Fits::get_header_block_pos() {
    int counter = 0;
    char buffer[BLOCK_SIZE];
    // char (&view)[8] = (char (&)[8])(*(buffer + 0));

    clear();
    seekg(0, std::ios::beg);

    do {
        read(buffer, BLOCK_SIZE);
        std::string str(buffer);
        if ((str.rfind("SIMPLE", 0) == 0) | (str.rfind("XTENSION", 0) == 0)) {
            header_start_block.push_back(counter);
            if (counter != 0)
                data_end_block.push_back(counter - 1);
        }
        counter++;

        if (str.rfind("END     ") != std::string::npos) {
            data_start_block.push_back(counter);
            header_end_block.push_back(counter - 1);
        }
    } while (!eof());
    data_end_block.push_back(counter - 2);

    clear();
    size = tellg();
    nblocks = size / BLOCK_SIZE;
    seekg(0, std::ios::beg);
}


