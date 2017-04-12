/**
 * @file   Encoder.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of utility class.
 *
 * Detailed description of file.
 */
#ifndef ITIVITI_DEV_ENCODER_H
#define ITIVITI_DEV_ENCODER_H
#include <climits>
#include <cstdint>

//!  A class intend to encode unsigned type big-endian to array of size to unsigned type.
/*!
  A utility class to Encode uint64_t to big-endian value to a uint8_t array of sizeof(uint64_t).

  The class contains only one member function
*/
class Encoder {
public:
    // Warning:  Untested preconditions (e.g., 0 <= size <= 8)
    int EncodeIntBigEndian(uint8_t dst[], uint64_t val, int offset, int size);

};

#endif //ITIVITI_DEV_ENCODER_H
