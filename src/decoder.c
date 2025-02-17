#include "../include/decoder.h"

#include "decoder.h"

size_t utf8_decode_length(uint8_t first_byte)
{
    if ((first_byte & 0x80) == 0)
        return 1;
    if ((first_byte & 0xE0) == 0xC0)
        return 2;
    if ((first_byte & 0xF0) == 0xE0)
        return 3;
    if ((first_byte & 0xF8) == 0xF0)
        return 4;
    return 0; // Invalid first byte
}

utf_result_t utf8_decode(const uint8_t *buffer, size_t buffer_size,
                         uint32_t *codepoint, size_t *bytes_read)
{
    if (!buffer || !codepoint || !bytes_read)
    {
        return UTF_INVALID_SEQUENCE;
    }

    *bytes_read = 0;
    *codepoint = 0;

    // Get sequence length from first byte
    size_t length = utf8_decode_length(buffer[0]);
    if (length == 0)
    {
        return UTF_INVALID_SEQUENCE;
    }

    // Check if we have enough bytes
    if (buffer_size < length)
    {
        return UTF_BUFFER_TOO_SMALL;
    }

    // Decode based on sequence length
    switch (length)
    {
    case 1:
        *codepoint = buffer[0];
        break;

    case 2:
        // Check continuation byte
        if ((buffer[1] & 0xC0) != 0x80)
        {
            return UTF_INVALID_SEQUENCE;
        }

        *codepoint = ((buffer[0] & 0x1F) << 6) |
                     (buffer[1] & 0x3F);

        // Check for overlong encoding
        if (*codepoint < 0x80)
        {
            return UTF_INVALID_SEQUENCE;
        }
        break;

    case 3:
        // Check continuation bytes
        if ((buffer[1] & 0xC0) != 0x80 ||
            (buffer[2] & 0xC0) != 0x80)
        {
            return UTF_INVALID_SEQUENCE;
        }

        *codepoint = ((buffer[0] & 0x0F) << 12) |
                     ((buffer[1] & 0x3F) << 6) |
                     (buffer[2] & 0x3F);

        // Check for overlong encoding
        if (*codepoint < 0x800)
        {
            return UTF_INVALID_SEQUENCE;
        }

        // Check for surrogate range
        if (*codepoint >= 0xD800 && *codepoint <= 0xDFFF)
        {
            return UTF_INVALID_SEQUENCE;
        }
        break;

    case 4:
        // Check continuation bytes
        if ((buffer[1] & 0xC0) != 0x80 ||
            (buffer[2] & 0xC0) != 0x80 ||
            (buffer[3] & 0xC0) != 0x80)
        {
            return UTF_INVALID_SEQUENCE;
        }

        *codepoint = ((buffer[0] & 0x07) << 18) |
                     ((buffer[1] & 0x3F) << 12) |
                     ((buffer[2] & 0x3F) << 6) |
                     (buffer[3] & 0x3F);

        // Check for overlong encoding
        if (*codepoint < 0x10000)
        {
            return UTF_INVALID_SEQUENCE;
        }

        // Check maximum valid Unicode codepoint
        if (*codepoint > 0x10FFFF)
        {
            return UTF_INVALID_SEQUENCE;
        }
        break;
    }

    *bytes_read = length;
    return UTF_SUCCESS;
}