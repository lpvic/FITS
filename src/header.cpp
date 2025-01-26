#include "header.h"

namespace fits {
    Header::Header(const std::vector<block_type>& blocks) {
        std::vector<byte_type> raw_header;

        raw_header.reserve(BLOCK_SIZE * blocks.size());
        for (auto elem : blocks) {
            raw_header.insert(raw_header.end(), elem.begin(), elem.end());
        }

        int counter = 0;
        for (int i = 0; i < raw_header.size(); i += HEADER_LINE_SIZE) {
            char (&view)[HEADER_LINE_SIZE] = (char (&)[HEADER_LINE_SIZE])(*(raw_header.data() + i));
            std::string line(view, HEADER_LINE_SIZE);
            
            if (trim_spcs(line) == "")
                continue;

            Keyword k(line);
            push_back(std::make_pair<>(k.keyword, k));
            counter++;
        }
    }

    std::vector<block_type> fits::Header::to_blocks() {
        std::vector<block_type> out;
        std::string temp_str = "";
        size_type nblocks = 0;
        size_type nfill = 0;

        for (auto it = begin(); it != end(); ++it) {
            temp_str += it->second.str().insert(it->second.str().size(), HEADER_LINE_SIZE - it->second.str().size(), ' ');
        }
        temp_str.insert(temp_str.size(), BLOCK_SIZE - (temp_str.size() % BLOCK_SIZE), ' ');

        nblocks = temp_str.size() / BLOCK_SIZE;
        if (nfill > 0) {
            ++nblocks;
        }

        for (auto it = temp_str.begin(); it != temp_str.end(); it = it + BLOCK_SIZE) {
            out.emplace_back(it, it + BLOCK_SIZE);
        }

        return out;
    }
}
