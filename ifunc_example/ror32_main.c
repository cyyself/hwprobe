#include <stdio.h>
#include <stdlib.h>
#include "ror32.h"

int main(int argc, char* argv[]) {
    unsigned int res = 0;
    long loop = 1e6;
    if (argc >= 2) loop = atol(argv[1]);
    for (long i=0;i<loop;i++) res ^= ror32(i, i % 32);
    printf("%d\n", res);
    return 0;
}
