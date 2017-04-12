/**
 * @file   Decoder.h
 * @Author Daniel Terranova (daniel.terranova@gmail.com)
 * @date   April, 2017
 * @brief  File contains declaration of utility class.
 *
 * Detailed description of file.
 */
#ifndef ITIVITI_DEV_DECODER_H
#define ITIVITI_DEV_DECODER_H

#include <cstdint>

//!  A class intend to decode big-endian array of size to unsigned type.
/*!
  A utility class to decode big-endian array of size to uint64_t.

  The class contains only one member function
*/
class Decoder {

public:
  /**
 * @name    Example API Actions
 * @brief   Example actions available.
 * @ingroup example
 *
 * This API provides utility member function
 *
 * @param [in] val array of bytes representing big-endian number of size .
 * @param [in] offset (zero indexed) where to start decoding process, usually 0
 *
 * @retval uint64_t the decoded value
 *
 * Example Usage:
 * @code
 *   uint64_t ret = DecodeIntBigEndian(val,0,sizeof(uint64_t));
 * @endcode
 * // Warning:  Untested preconditions (e.g., 0 <= size <= 8)
 */
  uint64_t DecodeIntBigEndian(uint8_t val[], int offset, int size);
        
};

#endif //ITIVITI_DEV_DECODER_H
