#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_BYTES 128

// Convert hex character to integer
int hex_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return -1;
}

// Convert hex string to byte array
int hex_to_byte(const char* hex, uint8_t* out, int max_out_len) {
    int len = strlen(hex);
    if (len % 2 != 0) return -1;

    int i;
    for (i = 0; i < len / 2 && i < max_out_len; ++i) {
        int hi = hex_to_int(hex[2 * i]);
        int lo = hex_to_int(hex[2 * i + 1]);
        if (hi == -1 || lo == -1) return -1;
        out[i] = (hi << 4) | lo;
    }
    return i;
}

// Score string by how "English-like" it is
double score_english(const uint8_t *data, int len) {
    double score = 0.0;
    for (int i = 0; i < len; ++i) {
        char c = data[i];
        if (isalpha(c)) score += 2.0;
        else if (isspace(c)) score += 1.0;
        else if (isprint(c)) score += 0.5;
        else score -= 1.0;
    }
    return score;
}

int main(void) {
    FILE *file = fopen("4.txt", "r");
    if (!file) {
        printf("Failed to open file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    uint8_t bytes[MAX_BYTES];
    uint8_t decoded[MAX_BYTES];
    char best_output[MAX_BYTES] = {0};

    double best_score = -1e9;
    int best_line_number = -1;
    uint8_t best_key = 0;

    int line_number = 0;
    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline
        size_t line_len = strlen(line);
        if (line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
            line_len--;
        }

        int byte_len = hex_to_byte(line, bytes, MAX_BYTES);
        if (byte_len <= 0) continue;

        // Try all possible single-byte XOR keys
        for (int key = 0; key < 256; ++key) {
            for (int i = 0; i < byte_len; ++i) {
                decoded[i] = bytes[i] ^ key;
            }

            double score = score_english(decoded, byte_len);
            if (score > best_score) {
                best_score = score;
                best_key = key;
                best_line_number = line_number;
                strncpy(best_output, (char *)decoded, byte_len);
                best_output[byte_len] = '\0';
            }
        }

        line_number++;
    }

    fclose(file);

    printf("Best line: %d\n", best_line_number + 1);
    printf("Best key: 0x%02X ('%c')\n", best_key, isprint(best_key) ? best_key : '?');
    printf("Decrypted message:\n%s\n", best_output);

    return 0;
}
