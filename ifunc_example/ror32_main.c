#include <stdio.h>
#include <stdlib.h>
#include "ror32.h"

int main(int argc, char* argv[]) {
    unsigned int res = 0;
    long loop = 1e6;
    if (argc >= 2) loop = atol(argv[1]);
    unsigned int *arr;
    long vsize = 256;
    if (argc >= 3) vsize = atol(argv[2]);
    arr = malloc(4 * vsize);
    for (long i=0;i<loop;i++) {
        for (int j=0;j<vsize;j++) arr[j] = j + i;
        ror32(arr, i % 32, vsize);
        for (int j=0;j<vsize;j++) res ^= arr[j];
    }
    printf("%d\n", res);
    free(arr);
    return 0;
}
