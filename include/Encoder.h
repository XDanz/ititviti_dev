//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_ENCODER_H
#define ITIVITI_DEV_ENCODER_H
#include <climits>
#include <cstdint>

class Encoder {
public:
    // Warning:  Untested preconditions (e.g., 0 <= size <= 8)
    int EncodeIntBigEndian(uint8_t dst[], uint64_t val, int offset, int size);

};

#endif //ITIVITI_DEV_ENCODER_H
