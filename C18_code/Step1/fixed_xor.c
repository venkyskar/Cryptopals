#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

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


// Converts byte array to hex string
void bytes_to_hex(const uint8_t *bytes, size_t len, char *hex_out) {
    const char *hex_chars = "0123456789abcdef";
    for (size_t i = 0; i < len; ++i) {
        hex_out[2*i]     = hex_chars[(bytes[i] >> 4) & 0x0F];
        hex_out[2*i + 1] = hex_chars[bytes[i] & 0x0F];
    }
    hex_out[2*len] = '\0';
}

// XORs two byte buffers
bool xor_buffers(const uint8_t *buf1, const uint8_t *buf2, uint8_t *result, size_t len) {
    if (!buf1 || !buf2 || !result) return false;

    for (size_t i = 0; i < len; ++i) {
        result[i] = buf1[i] ^ buf2[i];
    }
    return true;
}

// Test the function with given inputs
int main(void) {
    const char *hex1 = "1c0111001f010100061a024b53535009181c";
    const char *hex2 = "686974207468652062756c6c277320657965";

    size_t len1, len2;
    uint8_t *buf1 = malloc(strlen(hex1) / 2);
    uint8_t *buf2 = malloc(strlen(hex2) / 2);
    uint8_t *result = malloc(strlen(hex1) / 2);
    char *result_hex = malloc(strlen(hex1) + 1);

    if (!buf1 || !buf2 || !result || !result_hex) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (!hex_to_bytes(hex1, buf1, &len1) || !hex_to_bytes(hex2, buf2, &len2)) {
        fprintf(stderr, "Invalid hex input\n");
        return 1;
    }

    if (len1 != len2) {
        fprintf(stderr, "Buffers are not the same length\n");
        return 1;
    }

    xor_buffers(buf1, buf2, result, len1);
    bytes_to_hex(result, len1, result_hex);

    printf("XOR result (hex): %s\n", result_hex);

    // Optional: also print as ASCII
    printf("XOR result (ASCII): ");
    for (size_t i = 0; i < len1; ++i) {
        printf("%c", (result[i] >= 32 && result[i] <= 126) ? result[i] : '.');
    }
    printf("\n");

    free(buf1);
    free(buf2);
    free(result);
    free(result_hex);
    return 0;
}
