/*
2024 Autumn
*/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t prime1(size_t N);
size_t prime2(size_t N);
size_t prime3(size_t N);

int main() {
    size_t line_count;

    line_count = prime1(20);
    printf("prime1: L1 = %zu\n", line_count);

    line_count = prime2(20);
    printf("prime2: L1 = %zu\n", line_count);

    line_count = prime3(20);
    printf("prime3: L1 = %zu\n", line_count);
}
size_t prime1(size_t N) {
    size_t d = 2, t, l_count = 0;
    while (d <= N) {
        uint8_t isPrime = 1;
        t = 2;
        while (t < d) {
            if (d % t == 0) {
                isPrime = 0;
            }
            t++;
            l_count++;
        }
        if (isPrime) printf("%3zu,", d);
        d++;
    }
    printf("\n");
    return l_count;
}
size_t prime2(size_t N) {
    size_t d = 2, t, l_count = 0;
    uint8_t *isPrime = (uint8_t *)malloc(sizeof(uint8_t) * N);
    memset(isPrime, 1, sizeof(uint8_t) * N);
    while (d <= N) {
        if (isPrime[d]) {
            printf("%3zu,", d);
            t = d * d;
            while (t <= N) {
                isPrime[t] = 0;
                t = t + d;
                l_count++;
            }
        }
        d++;
    }
    printf("\n");
    free(isPrime);
    return l_count;
}
size_t prime3(size_t N) {
    size_t d = 3, t, l_count = 0;
    uint8_t *isPrime = malloc(sizeof(uint8_t) * (N / 2));
    memset(isPrime, 1, sizeof(uint8_t) * (N / 2));

    while (d <= N) {
        if (isPrime[(d - 1) / 2]) {
            printf("%3zu,", d);
            t = d * d;
            while (t <= N) {
                isPrime[(t - 1) / 2] = 0;
                t = t + 2 * d;
                l_count++;
            }
        }
        d = d + 2;
    }
    free(isPrime);
    printf("\n");
    return l_count;
}