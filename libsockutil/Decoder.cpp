//
// Created by danter on 2017-04-10.
//

#include <climits>
#include "Decoder.h"

uint64_t Decoder::decodeIntBigEndian(uint8_t *val, int offset, int size) {
    uint64_t rtn = 0;
    for (int i = 0; i < size; i++) {
        rtn = (rtn << CHAR_BIT) | val[offset + i];
    }
    return rtn;
}