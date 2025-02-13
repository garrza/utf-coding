#ifndef UTF_ENCODER_H
#define UTF_ENCODER_H

#include <stdint.h>
#include <stddef.h>

// UTF-8 Encoding
// Returns number of bytes needed to encode this codepoint
size_t utf8_encode_length(uint32_t codepoint, char *buffer);

// Encodes codepoint into buffer, returns bytes written
size_t utf8_encode(uint32_t codepoint, uint8_t *buffer);

// Returns codepoint size from first byte
size_t utf8_codepoint_size(uint8_t byte);

// Decodes bytes into codepoint, returns bytes consumed
size_t utf8_decode(const uint8_t *buffer, uint32_t *codepoint);

// UTF-16 Encoding
// Returns number of bytes needed to encode this codepoint
size_t utf16_encode_length(uint32_t codepoint, char *buffer);

// Encodes codepoint into buffer, returns bytes written
size_t utf16_encode(uint32_t codepoint, uint8_t *buffer);

size_t utf16_codepoint_size(uint8_t byte);

#endif // UTF_ENCODER_H