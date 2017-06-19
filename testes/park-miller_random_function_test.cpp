#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>

#define M 2147483647 /* 2^31 - 1 (Um número primo grande) */
#define A 16807      /* Número primo raiz de M, passa os testes estatisticos e produz um ciclo completo */
#define Q 127773     /* M / A (Para evitar overflow em A * seed) */
#define R 2836       /* M % A (Para evitar overflow em A * seed) */

unsigned int lcg_parkmiller(unsigned int seed) {
    unsigned int hi = seed / Q;
    unsigned int lo = seed % Q;
    unsigned int test = A * lo - R * hi;
    if (test <= 0)
        test += M;
    return test;
}

unsigned int getSeed(){
    return std::time(0) % rand()*rand();
}

unsigned int getRandomBetween(unsigned int min, unsigned int max){
    unsigned int randomNumber = lcg_parkmiller(getSeed());
    
    return (randomNumber % (max + 1 - min)) + min;
}

int main() {
    srand(time(0));
    
    for(int i = 0; i < 10; i++){
        printf("%u\n", getRandomBetween(1,100));
    }
        
}
