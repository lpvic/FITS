#ifndef __DATA_H__
#define __DATA_H__

namespace fits {
    class Data : public std::vector<byte_type> {
        public:
            Data(const std::vector<block_type>& blocks);
    };
}
#endif
