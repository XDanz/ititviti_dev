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
  A utility class to Encode uint64_t to big-endian array of uint8_t of sizeof(uint64_t).

  The class contains only one member function
*/
class Encoder {
public:
    /**
* @name    encodeIntBigEndian
* @brief   encode unsigned type big-endian to array of <p>size</p> to unsigned type.
* @ingroup example
*
* This API provides utility member function
*
* @param [in] dst array of bytes where the bytes will be stored.
* @param [in] val the value to be encoded
* @param [in] offset (zero indexed) where to start decoding process, usually 0
* @param [in] size in bytes of the val
*
* @retval number of bytes encoded
*
* Example Usage:
* @code
*   int ret = encoder.encodeIntBigEndian(val,0,sizeof(uint64_t));
* @endcode
* // Warning:  Untested preconditions (e.g., 0 <= size <= 8)
*/
    int encodeIntBigEndian(uint8_t *dst, uint64_t val, int offset, int size);

};

#endif //ITIVITI_DEV_ENCODER_H
