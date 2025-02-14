#include "../include/encoder.h"

size_t utf8_encode_length(uint32_t codepoint)
{
    if (codepoint <= 0x7F)
    {
        return 1;
    }
    else if (codepoint <= 0x7FF)
    {
        return 2;
    }
    else if (codepoint <= 0xFFFF)
    {
        return 3;
    }
    else if (codepoint <= 0x10FFFF)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

utf_result_t utf8_encode(uint32_t codepoint, uint8_t *buffer, size_t buffer_size, size_t *bytes_written)
{
    if (!buffer || !bytes_written)
        return UTF_INVALID_SEQUENCE;

    *bytes_written = 0;

    // Validate codepoint range
    if (codepoint > 0x10FFFF)
    {
        return UTF_INVALID_CODEPOINT;
    }

    // Get required buffer size
    size_t required_size = utf8_encode_length(codepoint);
    if (required_size == 0)
    {
        return UTF_INVALID_CODEPOINT;
    }

    if (buffer_size < required_size)
    {
        return UTF_BUFFER_TOO_SMALL;
    }

    // Encode based on size required
    if (codepoint <= 0x7F)
    {
        // Single byte ASCII
        buffer[0] = (uint8_t)codepoint;
        *bytes_written = 1;
    }
    else if (codepoint <= 0x7FF)
    {
        // Two bytes
        buffer[0] = 0xC0 | (uint8_t)(codepoint >> 6);
        buffer[1] = 0x80 | (uint8_t)(codepoint & 0x3F);
        *bytes_written = 2;
    }
    else if (codepoint <= 0xFFFF)
    {
        // Three bytes
        buffer[0] = 0xE0 | (uint8_t)(codepoint >> 12);
        buffer[1] = 0x80 | (uint8_t)((codepoint >> 6) & 0x3F);
        buffer[2] = 0x80 | (uint8_t)(codepoint & 0x3F);
        *bytes_written = 3;
    }
    else
    {
        // Four bytes
        buffer[0] = 0xF0 | (uint8_t)(codepoint >> 18);
        buffer[1] = 0x80 | (uint8_t)((codepoint >> 12) & 0x3F);
        buffer[2] = 0x80 | (uint8_t)((codepoint >> 6) & 0x3F);
        buffer[3] = 0x80 | (uint8_t)(codepoint & 0x3F);
        *bytes_written = 4;
    }

    return UTF_SUCCESS;
}
