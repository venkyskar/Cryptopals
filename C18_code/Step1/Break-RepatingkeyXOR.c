#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
#include <ctype.h>

#define MAXC 4096
#define MIN_K 2
#define MAX_K 40
#define BLOCKS 4

// Count bits in byte
static int popcount(uint8_t b) {
    int c = 0;
    while (b) { c += b & 1; b >>= 1; }
    return c;
}

// Hamming distance
static int hamming(const uint8_t *a, const uint8_t *b, int n) {
    int dist = 0;
    for (int i = 0; i < n; i++)
        dist += popcount(a[i] ^ b[i]);
    return dist;
}

// English scoring: weighted common letters
static double score_text(const uint8_t *p, int len) {
    static const double freq[26] = {
        8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,
        0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,
        6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074
    };
    double s = 0;
    for (int i = 0; i < len; i++) {
        char c = p[i];
        if (isalpha(c))
            s += freq[tolower(c) - 'a'];
        else if (isspace(c))
            s += 5.0;
        else if (isprint(c))
            s += 0.5;
        else
            s -= 5.0;
    }
    return s;
}

// Single-byte XOR breaker
static uint8_t break_xor(const uint8_t *data, int len) {
    double best = -DBL_MAX;
    uint8_t key = 0, tmp[MAXC];
    for (int k = 0; k < 256; k++) {
        for (int i = 0; i < len; i++)
            tmp[i] = data[i] ^ k;
        double sc = score_text(tmp, len);
        if (sc > best) { best = sc; key = k; }
    }
    return key;
}

// Base64 decode inline
static int b64val(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}
static int b64decode(const char *in, uint8_t *out) {
    int val = 0, bits = 0, len = 0;
    while (*in) {
        int v = b64val(*in++);
        if (v < 0) continue;
        val = (val << 6) | v;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out[len++] = (val >> bits) & 0xFF;
        }
    }
    return len;
}

int main(void) {
    FILE *f = fopen("sample1.txt", "r");
    if (!f) return 1;
    char b64[MAXC*2]={0}, line[128];
    while (fgets(line, sizeof(line), f))
        strncat(b64, line, sizeof(b64)-1-strlen(b64));
    fclose(f);

    uint8_t ct[MAXC];
    int ctlen = b64decode(b64, ct);

    // estimate keysize via averaged normalized Hamming distance
    double best_norm = DBL_MAX; int best_k = MIN_K;
    for (int ks = MIN_K; ks <= MAX_K && ks*BLOCKS <= ctlen; ks++) {
        double total = 0;
        int comparisons = 0;
        for (int i = 0; i < BLOCKS; i++) {
            for (int j = i+1; j < BLOCKS; j++) {
                total += hamming(ct + i*ks, ct + j*ks, ks) / (double)ks;
                comparisons++;
            }
        }
        double norm = total / comparisons;
        if (norm < best_norm) { best_norm = norm; best_k = ks; }
    }

    int ks = best_k;
    uint8_t key[MAX_K]={0}, pt[MAXC];

    // transpose and break each single-byte
    for (int i = 0; i < ks; i++) {
        uint8_t buf[MAXC];
        int blen = 0;
        for (int j = i; j < ctlen; j += ks)
            buf[blen++] = ct[j];
        key[i] = break_xor(buf, blen);
    }

    printf("Recovered key: ");
    for (int i = 0; i < ks; i++)
        printf("%c", isprint(key[i]) ? key[i] : '?');
    printf("\n\nDecrypted:\n");

    for (int i = 0; i < ctlen; i++)
        pt[i] = ct[i] ^ key[i % ks];

    fwrite(pt, 1, ctlen, stdout);
    return 0;
}
