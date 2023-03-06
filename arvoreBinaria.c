/* 
Implementação dos algoritmos de insercao - busca - remocao para Arvore binaria em C 
Compilador:/* Compilador: Dev-C++ versão 5.11         
Complexidade: O(log n) no pior caso. Insercao, busca  e remocao sao de complexidade Insert operation is O(N), Search Operation is O(N) & Delete Operation is O(N),
*/
#include <stdio.h>
#include <stdlib.h>

//struct no da arvore
struct no {
	int dado;
	struct no* esquerda;
  	struct no* direita;
};

//Funcao para criar novo no
struct no* novoNo(int dado)
{
	struct no* aux = (struct no*)malloc(sizeof(struct no));
	aux->dado = dado;
	aux->esquerda = aux->direita = NULL;
	return aux;
}

//Funcao para inserir.
struct no* insercao(struct no* raiz, int dado)
{
	//Se a arvore estiver vazia, retornada o novo no
	if (raiz == NULL)
		return novoNo(dado);

	//Caso a arvore nao esteja vazia e o elemento a ser adicionado e menor que o da raiz, sera adicionado a esquerda
	if (dado < raiz->dado)
		raiz->esquerda = insercao(raiz->esquerda, dado);
	else if (dado > raiz->dado) // Caso a arvore nao esteja vazia e o elemento a ser adicionado e maior que o da raiz, sera adicionado a direita
		raiz->direita = insercao(raiz->direita, dado);

	//retorna a raiz
	return raiz;
}

//Funcao que ira procurar o menor valor, ou seja, sempre ira para esquerda
struct no* menorNo(struct no* raiz)
{
	struct no* aux = raiz;

	//Ira descer para a esquerda ate encontrar o menor valor
	while (aux && aux->esquerda != NULL)
		aux = aux->esquerda;

	return aux;
}

//Funcao para remover um no da arvore binaria
struct no* remocao(struct no* raiz, int dado)
{
	// caso nao exista mais elementos na arvore
	if (raiz == NULL)
		return raiz;

	//Se o no a ser deletado for menor que a raiz, sera procurado na esquerda.
	if (dado < raiz->dado)
		raiz->esquerda = remocao(raiz->esquerda,dado);

	//Se o no a ser deletado for maior que a raiz, sera procurado na direita.	
	else if (dado > raiz->dado)
		raiz->direita = remocao(raiz->direita, dado);

	//Se o no a ser deletado estiver na raiz em questao
	else {
		// caso o no tenha apenas um filho ou sem filhos
		if (raiz->esquerda == NULL) {
			struct no* aux = raiz->direita;
			free(raiz);
			return aux;
		}
		else if (raiz->direita == NULL) {
			struct no* aux = raiz->esquerda;
			free(raiz);
			return aux;
		}

		//Caso o no tenha doiis filhos, ira procurar o menor valor para ser o sucessor do no raiz
		struct no* aux = menorNo(raiz->direita);

		// Ira copiar o proximo elemento para a raiz
		raiz->dado = aux->dado;

		// Delete the inorder successor
		raiz->direita = remocao(raiz->direita, aux->dado);
	}
	return raiz;
}

//Funcao para imprimir em Extensao
void imprimirExtensao(struct no* raiz){
  	if (raiz == NULL)	return;
  	if(raiz->esquerda != NULL) printf("%d ->",raiz->esquerda->dado);
  	if(raiz->direita != NULL) printf("%d ->",raiz->direita->dado);
  	if(raiz->esquerda != NULL) 	imprimirExtensao(raiz->esquerda);
  	if(raiz->direita != NULL) imprimirExtensao(raiz->direita);

}

//Funcao para imprimir em Profundidade
void imprimirProfundidade(struct no* raiz) {
  	if (raiz == NULL)
  		return;
	printf("%d ->", raiz->dado);
  	imprimirProfundidade(raiz->esquerda);
  	imprimirProfundidade(raiz->direita);
}

//Função de busca em arvore binaria
struct no* busca(struct no* raiz, int dado) {
 	if(raiz == NULL) {
 		printf("Elemento nao encontrado.\n");
  		return NULL;
 	}
 	
 	if(dado == raiz->dado)
 		{
 			printf("Elemento encontrado.");
 			return raiz; 
		 }
 		
 		
	else if(dado < raiz->dado){
		busca(raiz->esquerda, dado);
	}
	else if(dado > raiz->dado){
		busca(raiz->direita, dado);
 	}
 	
 	//return 0;
}


int main() {
	
	//Iniciando a arvore
	struct no* raiz = NULL;
	raiz = insercao(raiz, 50);
	raiz = insercao(raiz, 17);
	raiz = insercao(raiz, 72);
	raiz = insercao(raiz, 12);
	raiz = insercao(raiz, 23);
	raiz = insercao(raiz, 54);
	raiz = insercao(raiz, 78);
	raiz = insercao(raiz, 9);
	raiz = insercao(raiz, 14);
	raiz = insercao(raiz, 19);
	raiz = insercao(raiz, 67);
	 
	//Declarando variaveis para o menu	
	int escolha,dado, escolhaimprimir,c=1; 
	
	printf("Bem vindo(a) ao Trabalho de Arvore Binaria.\n\n");
		
  	do{
  		printf("---------------------------------------------------\n\n");
  		printf("Selecione a sua opcao:\n");
 		printf("1.Insercao de um no na Arvore Binaria\n");
    	printf("2.Remocao de um no na Arvore Binaria\n");
		printf("3.Imprimir a Arvore Binaria\n");
		printf("4.Buscar na Arvore Binaria\n");
		printf("5.Sair\n\n\n");
  		scanf("%d", &escolha);
  	switch (escolha){
			
		case 1://Caso deseje inserir um elemento
			printf("Digite o dado do no(Usar numeros apenas):\n");
	   		scanf("%d", &dado);
	    	raiz = insercao (raiz, dado);
	    	printf("No %d inserido com sucesso");
	    	break;	
				
			
		case 2://Caso deseje remover um dado.
				
			printf("Digite o dado que sera deletado-:");
    		scanf("%d", &dado);
    		raiz=remocao(raiz,dado);
    		if (raiz == NULL)
				printf("Arvore esta vazia");
    		else 
				printf("No %d removido com sucesso",dado);
    		break;
	  		
		case 3://Caso deseje imprimir
  			
			printf("Digite a opcao que deseja o tipo de impressao:\n");
			printf("1-Por Extensao \n2-Por Profundidade \n");
			scanf("%d",&escolhaimprimir);
	  			
			if(escolhaimprimir == 1){
	   			printf("Impressao por Extensao: \n");
	   			printf("%d ->", raiz->dado);
				imprimirExtensao(raiz);
				break;				
			}			
			else if(escolhaimprimir == 2){
	  			printf("\nImpressao por Profundidade: \n");
	  			imprimirProfundidade(raiz);
				break;			
			}
			else{
				printf("Opcao invalida. Retornando ao menu principal.\n");
				break;
			}
			
		case 4://Caso deseje buscar um elemento. Nesse caso, sera criado um ponteiro aux para receber o ponteiro que esta sendo buscado.

			printf("Digite o dado que sera buscado:\n");
			scanf("%d", &dado);
			struct no* aux = busca(raiz, dado);
			break;
				
		case 5://Caso deseje sair do programa
				
			printf("\nDeseja continuar no programa? Caso sim, digite 1. Caso nao, digite outro valor. \n\n");
	  		scanf("%d", &c);
	  		printf("-----\n");
	  		break;
  			
	  	default:
		    	printf("Escolha invalida. Por favor,selecione a opcao correta.\n");
  	}
  } while (c == 1);
  printf("Obrigado por utilizar a Arvore binaria");
}
