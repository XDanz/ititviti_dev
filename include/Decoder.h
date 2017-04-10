//
// Created by danter on 2017-04-10.
//

#ifndef ITIVITI_DEV_DECODER_H
#define ITIVITI_DEV_DECODER_H

class Decoder {
// Warning:  Untested preconditions (e.g., 0 <= size <= 8)
public:
    static uint64_t DecodeIntBigEndian(uint8_t val[], int offset, int size);
        
};

#endif //ITIVITI_DEV_DECODER_H
