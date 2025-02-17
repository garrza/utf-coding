#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include <stddef.h>

// Error codes for encoder operations
typedef enum
{
    UTF_SUCCESS = 0,
    UTF_INVALID_CODEPOINT,
    UTF_BUFFER_TOO_SMALL,
    UTF_INVALID_SEQUENCE
} utf_result_t;

// Gets the number of bytes needed to decode a codepoint
size_t utf8_decode_length(const uint8_t *buffer, size_t buffer_size);

// Decodes a UTF-8 sequence into a Unicode codepoint
// Returns UTF_SUCCESS on success, error code otherwise
// *bytes_read will contain the number of bytes read from buffer
utf_result_t utf8_decode(const uint8_t *buffer, size_t buffer_size,
                         uint32_t *codepoint, size_t *bytes_read);

#endif // DECODER_H