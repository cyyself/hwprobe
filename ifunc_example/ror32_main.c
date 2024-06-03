#include <stdio.h>
#include <stdlib.h>
#include "ror32.h"

int main(int argc, char* argv[]) {
    unsigned int res = 0;
    long loop = 1e6;
    if (argc >= 2) loop = atol(argv[1]);
    for (long i=0;i<loop;i++) {
        unsigned int arr[64];
        for (int j=0;j<64;j++) arr[j] = j + i;
        ror32(arr, i % 32, 64);
        for (int j=0;j<64;j++) res ^= arr[j];
    }
    printf("%d\n", res);
    return 0;
}
