//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_FILE_HANDLER_H
#define MINALEAR_FILE_HANDLER_H

#include <cstdint>

namespace minalear {
    const char *read_file(const char *filename);
    const char *read_binary_file(const char *filename, uint32_t &file_size);
}

#endif //MINALEAR_FILE_HANDLER_H
