/*
Implementação dos algoritmos de insercao - busca - remocao e ordenação para uma Tabela Hash com 4 posições para receber um conjunto de 9 chaves reais K. 
O algoritmo deverá exibir para o usuário a opção de tratamento de colisão por encadeamento. 
Compilador: GCC no Windows
Comandos: gcc tabelaHash.c  para compilar   		a    para executar
Obs:A ordenacao e feita no momento da insercao
Complexidade: Se for encontrado na primeira posição da tabela:O(1). Caso não, esteja só no final, seria O(n) por causa dos for
*/


#include<stdio.h>
#include<stdlib.h>

//Tamanho e o numero de posicoes permitidos na hash.ELEMENTOSMAX sao o numero de chaves permitidas. ELEMENTOS sao os numeros de elementos que ja estao cadastrados
#define TAM 4
int ELEMENTOSMAX=9;
int ELEMENTOS=0;

//set e a struck dos elementos hash.
struct set
{
	int chave;
    int data;
    struct set *prox;
};

struct set *elementos[TAM];

void iniciar(){
    int i;
    for(i = 0; i < TAM; i++)
        elementos[i] = NULL;
}

void insercao(int data){
    //Cria um novo elemento.
    struct set *novoElemento = malloc(sizeof(struct set));
    novoElemento->data = data;
    novoElemento->prox = NULL;

    //Calcula a chave hash pelo meotodo da divisao
    int chave = data % TAM;
    novoElemento->chave = chave;

    //checa se os elementos estao vazios
    if(elementos[chave] == NULL){
    	elementos[chave] = novoElemento;
    	ELEMENTOS++;
    	printf("Elemento inserido com sucesso. Numero de elementos:%d de no max:%d\n",ELEMENTOS, ELEMENTOSMAX);

	} 
    //tratamento de colisao por encadeamento
    else{
        printf("\n Ocorreu uma colisao. Deseja colocar esta chave nesta posicao? Sera utilizado o tratamento de colisao por encadeamento.  \n");
		printf("Caso sim, digite 1. Caso nao, digite qualquer outro numero\n");
		int z;
		scanf("%d",&z);
		if(z==1){
			struct set *auxPont = elementos[chave];
        	while(auxPont->prox){
           		auxPont = auxPont->prox;
       		}
			auxPont->prox = novoElemento;
    		ELEMENTOS++;
    		printf("Elemento inserido com sucesso. Numero de elementos:%d de no max:%d\n",ELEMENTOS, ELEMENTOSMAX);	  
		}
    }
}

void remocao(int dado){
  	int chave = dado % TAM;
  		//auxPont ira na frente para procurar o dado a ser deletado. aux2Pont ira ser o ponteiro anterior ao que vai ser deletado
  	if(elementos[chave] == NULL)
  		printf("Nao existe este dado para deletar.");
  		
	else{
	    struct set *auxPont = elementos[chave];
	    struct set *aux2Pont = elementos[chave];
	    while(auxPont){
	       	//Se encontrar o dado a ser deletado
	        if (auxPont->data == dado){
	       	//Caso for o ultimo elemento da posicao
				if(auxPont->prox == NULL){
					//Caso o ultimo elemento tambem for o primeiro.
					if(auxPont == aux2Pont){
						elementos[chave] = NULL;
					}
					else{
							aux2Pont->prox=NULL;
						}				
					}
				//Caso nao for o ultimo, ira ajeitar os ponteiros.
				else{
					//Caso o primeiro elemento sera deletado mas existem outros
					if (auxPont == aux2Pont){
						elementos[chave] = auxPont->prox;
					}		
					//Caso o elemento deletado nao seja o primeiro nem o ultimo.	
					else{
						aux2Pont->prox = auxPont->prox;
					}	
				}
				ELEMENTOS --;
				printf("Dado removido com sucesso\n");	
			}
		//Se não encontrar o dado, vai buscar no próximo.	aux2Pont fica um ponteiro atras do auxPont
		aux2Pont = auxPont;
		auxPont = auxPont->prox;	

		}
	}
}

void imprimir(){
    int i;
    for(i = 0; i < TAM; i++){
        struct set *auxPont = elementos[i];
        printf("Posicao[%d]-->",i);
        while(auxPont){
            printf("Chave: %d, Dado: %d-->",auxPont->chave,auxPont->data);
            auxPont = auxPont->prox;
        }
         printf("NULL\n");
    }
    printf("Numero de elementos:%d de no max:%d\n",ELEMENTOS, ELEMENTOSMAX);	 
}

void buscar(int dado){
	//count so serve para caso nao encontrar o dado, mostrar que nao foi encontrado
	int i,count=0;
	printf("Posicao do dado %d buscado:\n",dado);
    for(i = 0; i < TAM; i++){
        struct set *auxPont = elementos[i];
        while(auxPont){
            if (auxPont->data == dado){
            	printf("Dado encontrado na posicao %d\n",i);
            	count++;
			}
			auxPont = auxPont->prox;
        }
  	}
  	if (count == 0)
  		printf("Dado nao encontrado.\n");
}


int main(){
    //Inicia uma lista de ponteiros nulos na Hash
    iniciar();
  	int escolha, dado;
  	int c = 1;//usada para o switch 

	printf("Bem vindo(a) ao Implementacao dos algoritmos de insercao - busca - remocao e ordenacao para uma Tabela Hash.\n\n");
		
  	do{
  		printf("---------------------------------------------------\n\n");
  		printf("Selecione a sua opcao:\n");
 		printf("1.Insercao de um item na tabela Hash\n");
    	printf("2.Remocao de um item na tabela Hash\n");
		printf("3.Imprimir a tabela Hash\n");
		printf("4.Buscar na tabela Hash\n");
		printf("5.Sair\n\n\n");
  		scanf("%d", &escolha);
  	switch (escolha){
  		
 		case 1:
			if(ELEMENTOSMAX>ELEMENTOS){
			   	printf("Digite o dado armazenado(Usar numeros apenas):\n");
   				scanf("%d", &dado);
    			insercao(dado);
    			break;				
			}
			else{
				printf("Numero de elementos na tabela ja excedeu o limite de %d\n",ELEMENTOSMAX);
				break;
			}


  		case 2:

    		printf("Digite o dado que sera deletado-:");
    		scanf("%d", &dado);
    		remocao(dado);
    		break;

  		case 3:
    		imprimir();
    		break;
		
		case 4:
		
			printf("Digite o dado que sera buscado:\n");
			scanf("%d", &dado);
			buscar(dado);
			break;
			
		case 5:
			
		  	printf("\nDeseja continuar no programa? Caso sim, digite 1. Caso nao, digite outro valor. \n\n");
  			scanf("%d", &c);
  			printf("-----\n");
  			break;
  			
  		default:
	    printf("Escolha invalida. Por favor,selecione a opcao correta.\n");
  	}
  } while (c == 1);
  printf("Obrigado por utilizar a Tabela Hash");
}
