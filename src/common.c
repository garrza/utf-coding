#ifndef COMMON_H
#define COMMON_H

/*
UTF-8: Variable length encoding system where each codepoint is encoded into 1-4 bytes
The first byte of the encoding is used to determine the number of bytes in the encoding
1 byte: 0xxxxxxx
2 bytes: 110xxxxx 10xxxxxx
3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

UTF-16: Variable length encoding system as well, typically uses 2 bytes for most characters
but 3 bytes for characters outside BMP (e.g. emojis)
2 bytes: 110110xx 10xxxxxx
3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
*/

#endif // COMMON_H
