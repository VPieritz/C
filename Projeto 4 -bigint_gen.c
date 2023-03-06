/*gera um int aleatório pra high e um um numero aleatório entre 0 e 10^9 pra low... 
Se quiser algo pra ver se seu algoritmo funciona, use as linhas comentadas, vai gerar numeros de -5 a 4 e 0 a 9
Compilador: GCC
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define GEN 150
#define GEN 200000

typedef struct biggo{
    int high, low; 
}BigInt;

int rand_int(){
    int result=0;
    for(int i=0; i<32; i++){
        result = (result | (rand() % 2)) << 1;
    }
    return result;
}

BigInt* rand_bigint(){
    BigInt *bigint = malloc(sizeof(BigInt));

    bigint->high = rand_int();
    
    do{
        bigint->low = rand_int();
    }while(!(bigint->low >= 0 && bigint->low < 1000000000));

    return bigint;
}

int main(){
    srand(time(NULL));

    int i;
    BigInt *bigint;
    FILE *big_file = fopen("bigint.dat", "w");

    for(i=0; i<GEN; i++){
        bigint = rand_bigint();
        //fprintf(big_file, "%d %d \n", rand()%10 - 5, rand()%10);
        fprintf(big_file, "%d %d \n", bigint->high, bigint->low);
        free(bigint);
    }
    return 0;
}
