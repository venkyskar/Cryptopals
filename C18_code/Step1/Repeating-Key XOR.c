#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024
#define KEY "ICE"

// Convert byte to hex string (2 characters)
void byte_to_hex(uint8_t byte, char* out) {
    const char hex_chars[] = "0123456789abcdef";
    out[0] = hex_chars[(byte >> 4) & 0xF];
    out[1] = hex_chars[byte & 0xF];
}

int main(void) {
    FILE *infile = fopen("input.txt", "r");
    if (!infile) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    char plaintext[MAX_INPUT_SIZE];
    int len = 0;

    // Read the plaintext from file
    while (fgets(plaintext + len, MAX_INPUT_SIZE - len, infile)) {
        len = strlen(plaintext);
        if (len >= MAX_INPUT_SIZE - 1) break;  // prevent overflow
    }
    fclose(infile);

    const char *key = KEY;
    int key_len = strlen(key);

    // Output the hex-encoded ciphertext
    for (int i = 0; i < len; i++) {
        uint8_t p = (uint8_t)plaintext[i];
        uint8_t k = (uint8_t)key[i % key_len];
        uint8_t xored = p ^ k;

        char hex[3];
        byte_to_hex(xored, hex);
        hex[2] = '\0';
        printf("%s", hex);
    }

    printf("\n");
    return 0;
}
