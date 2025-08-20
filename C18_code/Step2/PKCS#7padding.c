#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

// Function to apply PKCS#7 padding
void pkcs7_pad(unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len) {
    unsigned char padding_len = BLOCK_SIZE - (input_len % BLOCK_SIZE);
    *output_len = input_len + padding_len;

    // Copy original input
    memcpy(output, input, input_len);

    // Append padding
    for (int i = 0; i < padding_len; i++) {
        output[input_len + i] = padding_len;
    }
}

int main() {
    unsigned char plaintext[] = "YELLOW SUBMARINE";
    size_t plaintext_len = strlen((char *)plaintext);
    unsigned char padded_output[BLOCK_SIZE * 2];  // Max possible size after padding
    size_t padded_len = 0;

    pkcs7_pad(plaintext, plaintext_len, padded_output, &padded_len);

    printf("Padded output (hex): ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02X ", padded_output[i]);
    }

    printf("\nPadded output (ASCII): ");
    for (size_t i = 0; i < padded_len; i++) {
        if (padded_output[i] >= 32 && padded_output[i] <= 126) {
            printf("%c", padded_output[i]);
        } else {
            printf("\\x%02X", padded_output[i]);
        }
    }

    printf("\n");
    return 0;
}




/***
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//                            Original Script
//------------------------------------------------------------------------------------------------------------------------------------------------------
  #include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_INPUT_LEN 255

// PKCS#7 padding function
uint8_t pkcs7_pad(uint8_t *buf, uint8_t input_len, uint8_t block_size) {
    if (block_size == 0 || block_size > 255) {
        return 0; // Invalid block size
    }

    if (input_len > MAX_INPUT_LEN || (input_len + block_size) > MAX_INPUT_LEN) {
        return 0; // Input too long to pad safely
    }

    uint8_t pad_len = block_size - (input_len % block_size);
    for (uint8_t i = 0; i < pad_len; i++) {
        buf[input_len + i] = pad_len;
    }

    return input_len + pad_len;
}

int main(void) {
    // Original input (e.g. "YELLOW SUBMARINE")
    uint8_t input_buf[MAX_INPUT_LEN] = "YELLOW SUBMARINE";
    uint8_t input_len = strlen((char *)input_buf);
    uint8_t block_size = 20;

    // Apply padding
    uint8_t padded_len = pkcs7_pad(input_buf, input_len, block_size);

    // Output result
    printf("Padded length: %d\n", padded_len);
    printf("Padded bytes (hex): ");
    for (uint8_t i = 0; i < padded_len; i++) {
        printf("%02X ", input_buf[i]);
    }
    printf("\n");

    return 0;
}
***/
