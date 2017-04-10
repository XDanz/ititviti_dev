//
// Created by danter on 2017-04-10.
//


#include "Encoder.h"

static int Encoder::EncodeIntBigEndian(uint8_t dst[], uint64_t val, int offset, int size) {
    for (int i = 0; i < size; i++) {
        dst[offset++] = (uint8_t) (val >> ((size - 1) - i) * CHAR_BIT);
    }
    return offset;
}
