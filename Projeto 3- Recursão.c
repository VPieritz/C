//Projeto que usa recursão para medir simulando uma balança

#include <stdio.h>
#include <stdlib.h>



void imprimeVetor(int *vetor, int n){
	int i;
	for(i=0;i<n;i++){
		if(vetor[i] != 0)
			printf("%d ",vetor[i]);
	}
	printf("\n");
}
/*Funcao recursiva que ira verificar 4 condicoes de cada Pi: 
-Se nao ha mais Pi para pesar;
-Se a soma de todos os pesos disponiveis sao menores que Pi
-Se o Pi e exatamente a soma dos pesos disponiveis
-Se a soma de pesos eh maior que Pi. Neste caso, ira comecar o balancemaento.
*/

int BALANCA(int M, int N,int *vetorPesos, int *vetorPi,int n,int soma){
	if (n == N)//Caso acabou o vetor de pesos a serem aferidos. Condicao de saida da recursividade
		return NULL;
	else if (vetorPi[n] > soma)//Caso Pi ser maior que a soma dos pesos
		printf("0\n");
	else if (vetorPi[n] == soma)// Caso Pi ser a soma de pesos.
		imprimeVetor(vetorPesos,M);
	else{//Caso Pi for menor que a soma de pesos, vai começar a fazer o balanceamento. 
		//Cria um vetorPesosUsados para armazenar os Pesos que serao usados para medir. 
		int m,vetorPesosUsados[M],resto = vetorPi[n];
		//Necessario colocar todos os valores igual a 0 para imprimeVetor nao imprimir um valor de peso que nao existe
		for (m=0;m<M;m++)
			vetorPesosUsados[m]= 0;

		
		for(m=0;m<M;m++){
			if(vetorPesos[m] == resto){//Se o Peso atual é igual ao Pi, ira imprimir todos os Pesos Usados e zerar o resto
			vetorPesosUsados[m]= vetorPesos[m];
			imprimeVetor(vetorPesosUsados,M);
			}
			
			else if(vetorPesos[m] < resto){// Se o Peso atual for menor que Pi, ira subtrair o valor do resto e seguir no laco
				resto -= vetorPesos[m];
				vetorPesosUsados[m]= vetorPesos[m];
				
			}
			else{//Se o peso atual for maior que Pi
				int j = m+1,somaaux=0,PesoAtual;
				PesoAtual = vetorPesos[m];
				for(j=j;j<M;j++)
					somaaux += vetorPesos[j];
				somaaux += resto;
				if(somaaux == PesoAtual){//Se a soma do resto com todos os outros pesos forem igual ao proximo peso a ser medido, entao colocara o peso na outra balanca
				//Exemplo: resto = 20, pesos que podem ser usados para medir: 30 e 10. Ira somar o 10 com 20, ver que 20+10=30 e entao colocar 10 do outro lado da balanca
					int aux;
					j=m;
					vetorPesosUsados[m]=PesoAtual;
					j++;
					for(j=j;j<M;j++){
						aux= 0;
						aux -= vetorPesos[j];
						vetorPesosUsados[j] = aux;
					}
					imprimeVetor(vetorPesosUsados, M);
					m=M;
				}
				else if(somaaux > PesoAtual)//Nesse caso, vai so passar para a proxima iteracao para ver se com pesos mais leves eh possivel comparar.
						printf("");//Prinft apenas para entrar nesse laco e nao nos outros.					
				else{//somaaux <PesoAtual , nesse caso, nao eh possivel medir. Exemplo: 31 com pesos 10 30 50
					somaaux += vetorPesos[m-1];
					if (somaaux< PesoAtual){//somaaux <PesoAtual , nesse caso, ira verificar se existem outros pesos mais leves alem do atual. Se sim, ira ignorar o atual e ir para o prox
					//Exemplo: PesoAtual eh 300, mas somaaux eh 210. Ira verificar se tem outros pesos mais leves alem do de 300 para ser o PesoAtual
						printf("0\n");
						m=M;	
					}
				}
			}
		}
	}
	n++;
	BALANCA(M,N, vetorPesos, vetorPi,n,soma);
}
//Metodo Bubble sort para deixar decrescente
void ORDENAVETOR(int *vet,int n){  
  	int i, j, min, swap,temp; 
 	for (i = 1; i < n; i++) {
   		for (j = 0; j < i; j++) {
        	if (vet[i] > vet[j]) {
            	temp = vet[i];
            	vet[i] = vet[j];
            	vet[j] = temp;
       		}
    	}	
	}
}

int SOMAVETOR(int *vetorPesos,int M){
	int aux=0,i;
	for (i=0;i<M;i++){
		aux += vetorPesos[i];
	}
	return aux;
}

int main(){
	int M,N,i,a=0,b=0,soma=0;
	printf("Valores permitidos:\n1<= Pi <= 10^6\n1<=N<=100\n5<=M<=20\n  ");
	printf("--------------------------\n");
	//Laco para manter as condicoes de N e M
	while(a == 0 || b==0){
		printf("Digite o valor de N e M:");
		scanf("%d%d",&N,&M);
		if(0< N && N<101)
			a=1;
		else{
			printf("Valor invalido de N. Valores de N permitidos:1<=N<=100\n");
			a=0;
		}
		if(M> 4 && M<21)
			b=1;
		else{
			printf("Valor invalido de M. Valores de M permitidos: 5<=M<=20\n");
			b=0;
		}
	}
	int vetorPesos[M];
	printf("Digite %d valores de pesos que serao usados para aferir a massa do produto ",M);
	//Laco para armazenar os valores de Pesos em um vetorPesos
	for(i=0;i<M;i++)
		scanf("%d",&vetorPesos[i]);
	int vetorPi[N];
	printf("Digite %d pesos(Pi) que serao aferidos:",N);
	//Laco para armazenar os valores de Pi em um vetorPi com as condicoes necessarias
	for(i=0; i<N;i++){
		scanf("%d",&vetorPi[i]);
		if(vetorPi[i]< 1 || vetorPi[i] > 1000000){
			printf("Valor invalido de Pi, valores permitidos:1<= Pi <= 10^6\n");
			i--;
		}
	}
	ORDENAVETOR(vetorPesos,M);
	soma = SOMAVETOR(vetorPesos,M);	
	BALANCA(M,N, vetorPesos, vetorPi,0,soma);
	
	return 0;
}
