#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

FILE *randomFile;

unsigned int getDevUrandomValue() {
    int byte_count = 32;
    int data[byte_count];
    
    fread(&data, 1, byte_count, randomFile);
    
    unsigned long soma = 0;
    
    for (int i = 0; i < byte_count; i++) {
        soma += data[i];
    }
    
    return soma / 10;
}

int main() {
    randomFile = fopen("/dev/urandom", "r");
    for(int i = 0; i < 10; i++)
        printf("%u\n", getDevUrandomValue());

    fclose(randomFile);
    return 0;
}
