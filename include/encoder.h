#ifndef ENCODER_H
#define ENCODER_H

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

// Gets the number of bytes needed to encode a codepoint
size_t utf8_encode_length(uint32_t codepoint);

// Encodes a Unicode codepoint to UTF-8
// Returns UTF_SUCCESS on success, error code otherwise
// *bytes_written will contain the number of bytes written to buffer
utf_result_t utf8_encode(uint32_t codepoint, uint8_t *buffer, size_t buffer_size, size_t *bytes_written);

#endif // ENCODER_H