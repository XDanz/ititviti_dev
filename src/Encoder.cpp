/**
 * @file   Encoder.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of utility class.
 *
 * Detailed description of file.
 */
#include "Encoder.h"

int Encoder::EncodeIntBigEndian(uint8_t dst[], uint64_t val, int offset, int size) {
    for (int i = 0; i < size; i++) {
        dst[offset++] = (uint8_t) (val >> ((size - 1) - i) * CHAR_BIT);
    }
    return offset;
}
