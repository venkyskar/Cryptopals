#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16
#define MAX_LINE_LEN 4096

// Convert hex character to value
unsigned char hex_char_to_val(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return 0;
}

// Convert hex string to bytes
int hex_to_bytes(const char *hex, unsigned char *bytes, int max_len) {
    int len = strlen(hex) / 2;
    if (len > max_len) return -1;
    for (int i = 0; i < len; i++) {
        bytes[i] = (hex_char_to_val(hex[2*i]) << 4) | hex_char_to_val(hex[2*i + 1]);
    }
    return len;
}

// Count repeating 16-byte blocks
int count_repeated_blocks(unsigned char *data, int len) {
    int blocks = len / BLOCK_SIZE;
    int count = 0;
    for (int i = 0; i < blocks; i++) {
        for (int j = i + 1; j < blocks; j++) {
            if (memcmp(data + i * BLOCK_SIZE, data + j * BLOCK_SIZE, BLOCK_SIZE) == 0) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    FILE *fp = fopen("sample1.txt", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[MAX_LINE_LEN];
    unsigned char bytes[MAX_LINE_LEN];
    int line_number = 0;
    int max_repeats = -1;
    int likely_ecb_line = -1;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';  // strip newline
        int byte_len = hex_to_bytes(line, bytes, sizeof(bytes));
        if (byte_len <= 0) continue;

        int repeats = count_repeated_blocks(bytes, byte_len);
        if (repeats > max_repeats) {
            max_repeats = repeats;
            likely_ecb_line = line_number;
        }
        line_number++;
    }

    fclose(fp);

    if (likely_ecb_line >= 0) {
        printf("Line %d is likely ECB encrypted (repeated blocks: %d)\n", likely_ecb_line + 1, max_repeats);
    } else {
        printf("No ECB encrypted line detected.\n");
    }

    return 0;
}
