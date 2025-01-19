#include "fits.h"
#include "utils.h"

#include <iostream>

Fits::Fits(const char* filename, ios_base::openmode mode) : std::fstream(filename, mode) {
    getHeaderBlockPosition();
}

Fits::Fits(const std::string& filename, ios_base::openmode mode) : std::fstream(filename, mode) {
    getHeaderBlockPosition();
}

void Fits::readBlock(char* buffer, const int n) {
    int counter = 0;

    this->clear();
    this->seekg(0, std::ios::beg);

    do {
        this->read(buffer, BLOCK_SIZE);
        counter++;
    } while (n >= counter);
}

void Fits::readBlock(char* buffer, const int from, const int to) {
    int counter = 0;

    this->clear();
    this->seekg(0, std::ios::beg);
    int bytesToRead = (to - from + 1) * BLOCK_SIZE;
    char* tmp;

    // go to first block beginning
    this->read(tmp, from * BLOCK_SIZE);
    
    // read the blocks
    if (to < this->nblocks)
        this->read(buffer, bytesToRead);
    else
        this->read(buffer, (nblocks - from) * BLOCK_SIZE);
}

void Fits::readHeader() {
    for (int i = 0; i < this->headerStartBlock.size(); i++) {
        this->readHeader(i);
    }
}

void Fits::readHeader(int n) {
    int startBlock = this->headerStartBlock[n];
    int endBlock = this->headerEndBlock[n];
    int bytesToRead = (endBlock - startBlock + 1) * BLOCK_SIZE;

    char *blocks = new char[bytesToRead];
    this->readBlock(blocks, startBlock, endBlock);

    unsorted_map<std::string, Keyword> keywords;
    int counter = 0;
    for (int i = 0; i < bytesToRead; i += HEADER_LINE_SIZE) {
        char (&view)[HEADER_LINE_SIZE] = (char (&)[HEADER_LINE_SIZE])(*(blocks + i));
        std::string line(view, HEADER_LINE_SIZE);
        
        if (trimSpaces(line) == "")
            continue;

        Keyword k(line);
        keywords.push_back(std::make_pair<>(k.keyword, k));
        counter++;
    }

    this->headers.insert({n, keywords});

    delete [] blocks;
}

void Fits::getHeaderBlockPosition() {
    int counter = 0;
    char buffer[BLOCK_SIZE];
    // char (&view)[8] = (char (&)[8])(*(buffer + 0));

    this->clear();
    this->seekg(0, std::ios::beg);

    do {
        this->read(buffer, BLOCK_SIZE);
        std::string str(buffer);
        if ((str.rfind("SIMPLE", 0) == 0) | (str.rfind("XTENSION", 0) == 0)) {
            this->headerStartBlock.push_back(counter);
            if (counter != 0)
                this->dataEndBlock.push_back(counter - 1);
        }
        counter++;

        if (str.rfind("END     ") != std::string::npos) {
            this->dataStartBlock.push_back(counter);
            this->headerEndBlock.push_back(counter - 1);
        }
    } while (!this->eof());
    this->dataEndBlock.push_back(counter - 2);

    this->clear();
    this->size = this->tellg();
    this->nblocks = this->size / BLOCK_SIZE;
    this->seekg(0, std::ios::beg);
}


