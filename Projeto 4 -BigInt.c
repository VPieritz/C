//Algoritmo le o bigint.dat, gerado pelo Projeto 4 -bigint_gen, coloca em um vetor de BigInt, ordena com o algoritmo
//desejado e escreve o vetor ordenado em shell.dat
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define size 200000

typedef struct biggo{
	int high;
	int low;
}BigInt;

//le do bigint.dat e os escreve no vetor de BigInt.
void readFile(BigInt* vetor){
	FILE *bigintFile;
	bigintFile = fopen("bigint.dat", "r");
	
	int cont=0;
	//Scaneara 2 valores de bigintFile.dat e colocara no vetor de BigInt
	while (!feof(bigintFile)){	
		fscanf(bigintFile, "%d", &vetor[cont].high);
		fscanf(bigintFile, "%d", &vetor[cont].low);
		cont++;
	}		
	fclose(bigintFile);
}

//Escreve no shell.dat os numeros do vetor de BigInt.
void writeFile(BigInt* vetor){
	FILE *shellFile;
	shellFile = fopen("shell.dat", "w");
	
	int	cont=0;
	while (cont != size){
		fprintf(shellFile, "%d %d \n", vetor[cont].high, vetor[cont].low);
		cont++;
	}
	fclose(shellFile);
}

//Algoritmo de ShellSort modificado para lidar com High e Low
void shellSortHighLow(BigInt* vetor) {
  int gap = 0,i,j,k,auxLow,auxHigh;

  while(gap < size/2)
    gap = gap*3+1;
  
  while(gap !=1){
    gap = gap/3;
    for(i=0;i<gap;i++){//Insercao p cada vetor inicia aqui
      for(j=i+gap;j<size;j+=gap){
      	//Mudanca aqui: Originalmente seria apenas k=j;
      	//E necessario setar os aux aqui para comparar nos lacos seguintes
        auxHigh = vetor[j].high;
        auxLow = vetor[j].low;
        k=j;
		
        while(k-gap>=0 && (vetor[k-gap].high > auxHigh)){
        //Unica mudanca aqui e a necessidade de troca tanto e high quanto low
          vetor[k].high= vetor[k-gap].high;          
          vetor[k].low = vetor[k-gap].low;
          k=k-gap;
        }
        //Esse laco a mais e necessario para comparar a parte low quando High sao identicos
        while(k-gap>=0 && (vetor[k-gap].low > auxLow)&& vetor[k-gap].high == auxHigh){
          vetor[k].high= vetor[k-gap].high;         
          vetor[k].low = vetor[k-gap].low;
          k=k-gap;
        }
        vetor[k].high=auxHigh;
        vetor[k].low=auxLow;
      }
    }
  }
}

//Algoritmo de SelectionSort modificado para lidar com High e Low
void selectionSortHighLow(BigInt* vetor){
	int i, j, menor, auxHigh,auxLow;
	for (i=0; i<size-1; i++){
		menor = i;
		for (j=i+1; j<size; j++)
			if (vetor[j].high < vetor[menor].high)
				menor = j;
			else if(vetor[j].high == vetor[menor].high){
				//If a mais por conta de precisar comparar o low quando high sao iguais
				if(vetor[j].low < vetor[menor].low)
					menor = j;
			}
		if (menor != i){//Ajustes aqui para o High e Low.
			auxHigh = vetor[i].high;
			auxLow = vetor[i].low;
			vetor[i].high = vetor[menor].high;
			vetor[i].low = vetor[menor].low;
			vetor[menor].high = auxHigh;
			vetor[menor].low = auxLow;
			/*selectionSort padrao:
			aux = vetor[i];
			vetor[i] = vetor[menor];
			vetor[menor] = aux;
			*/
		}
	}
}


int main() {
	float tInicio, tFim;
	int choice;
	BigInt *vetor;
	vetor = (BigInt *) malloc (size * sizeof(BigInt));

	printf("1-Shell, 2-Selection:");
	scanf("%d",&choice);
	tInicio = clock();
	readFile(vetor);
	
	if (choice ==1)
		shellSortHighLow(vetor);		
	else if(choice == 2)
		selectionSortHighLow(vetor);
	else 
		printf("Opcao invalida. Reinicie o programa.\n");
	
	tFim = clock();
	writeFile(vetor);
	printf("Tempo necessario para a ordenacao: %fs\n",(float) ((tFim - tInicio) / (CLOCKS_PER_SEC) ));
	
	return 0;
}
