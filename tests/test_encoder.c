#include <stdio.h>
#include "encoder.h"

void print_bytes(uint8_t *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}

int main()
{
    uint8_t buffer[4];
    size_t bytes_written;
    utf_result_t result;

    // Test 1: ASCII character 'A'
    result = utf8_encode(0x41, buffer, sizeof(buffer), &bytes_written);
    printf("Test 1 (ASCII 'A'): ");
    if (result == UTF_SUCCESS)
    {
        print_bytes(buffer, bytes_written);
    }
    else
    {
        printf("Error: %d\n", result);
    }

    // Test 2: 2-byte character '€' (0x20AC)
    result = utf8_encode(0x20AC, buffer, sizeof(buffer), &bytes_written);
    printf("Test 2 (Euro sign): ");
    if (result == UTF_SUCCESS)
    {
        print_bytes(buffer, bytes_written);
    }
    else
    {
        printf("Error: %d\n", result);
    }

    return 0;
}
