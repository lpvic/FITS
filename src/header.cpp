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

    std::vector<block_type>& fits::Header::to_blocks() {
        // TODO: insert return statement here
    }
}
