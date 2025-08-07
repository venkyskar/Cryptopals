#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

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

// Score how "English-like" a string is
double score_english(const uint8_t *data, size_t len) {
    double score = 0.0;
    for (size_t i = 0; i < len; ++i) {
        char c = data[i];
        if (isalpha(c)) score += 2.0;
        else if (isspace(c)) score += 1.0;
        else if (isprint(c)) score += 0.5;
        else score -= 1.0;
    }
    return score;
}

int main() {
    const char *hex_input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t hex_len = strlen(hex_input);
    uint8_t *cipher_bytes = malloc(hex_len / 2);
    uint8_t *decoded = malloc(hex_len / 2 + 1);

    int byte_len = hex_to_byte(hex_input, cipher_bytes, hex_len);
    if (byte_len <= 0) {
        fprintf(stderr, "Invalid hex string.\n");
        return 1;
    }

    double best_score = -1e9;
    uint8_t best_key = 0;
    char best_output[256] = {0};

    // Try all possible single-byte keys
    for (int key = 0; key <= 255; ++key) {
        for (int i = 0; i < byte_len; ++i) {
            decoded[i] = cipher_bytes[i] ^ key;
        }
        decoded[byte_len] = '\0';

        double score = score_english(decoded, byte_len);
        if (score > best_score) {
            best_score = score;
            best_key = key;
            strncpy(best_output, (char *)decoded, byte_len);
            best_output[byte_len] = '\0';
        }
    }

    printf("Best key: 0x%02X ('%c')\n", best_key, isprint(best_key) ? best_key : '?');
    printf("Decrypted message:\n%s\n", best_output);

    free(cipher_bytes);
    free(decoded);
    return 0;
}
