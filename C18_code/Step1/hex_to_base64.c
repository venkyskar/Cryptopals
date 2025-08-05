#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// Base64 encoding table
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Convert a hex character to integer
int hex_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return -1;  // Invalid hex digit
}

// Convert hex string to byte array

int hex_to_byte(const char* hex, uint8_t* out, int max_out_len) {
    int len = strlen(hex);
    if (len % 2 != 0) return -1;  // Hex must be even-length

    int i;
    for (i = 0; i < len / 2 && i < max_out_len; i++) {
        int hi = hex_to_int(hex[2 * i]);
        int lo = hex_to_int(hex[2 * i + 1]);
        if (hi == -1 || lo == -1) return -1;  // Invalid hex digit
        out[i] = (hi << 4) | lo;
    }
    return i;  // number of bytes
}

// Base64 encode function

void base64_encode(const uint8_t* in, int in_len, char* out) {
    int i, j;
    int out_index = 0;

    for (i = 0; i < in_len; i += 3) {
        uint32_t buf = 0;
        int padding = 0;

        // Combine up to 3 bytes into a 24-bit buffer
        for (j = 0; j < 3; j++) {
            buf <<= 8;
            if (i + j < in_len) {
                buf |= in[i + j];
            } else {
                padding++;
            }
        }

        // Extract four 6-bit segments and map to Base64 characters
        for (j = 0; j < 4; j++) {
            if (j <= 3 - padding) {
                out[out_index++] = base64_table[(buf >> (18 - 6 * j)) & 0x3F];
            } else {
                out[out_index++] = '=';
            }
        }
    }

    out[out_index] = '\0';  // Null-terminate
}
