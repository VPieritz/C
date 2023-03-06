/*
Explicacao geral: Programa ira armazenar 2 listas, uma que sera usada para Entrada de dados do usuario e outra que sera a de Espera(que tambem sera a saida de dados).
Estas duas listas serao criadas priorizando variaveis diferentes, para seguir a ordem exigida pelo projeto
A funcao ControleCaixa ira gerenciar quem esta no(s) caixa(s), quem deve entrar na lista de Espera e quando imprimir a saida a partir do instante T dada pela lista de Entrada.
Para Isso, precisara do vetorCaixas, que ira mostrar ate quando o caixa estara ocupado e qual(is) caixas estarao desocupados no instante T
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct fila{
	int I;
	int T;
	int D;
	struct fila* prox;
}fila;

//Funcao para validar o N pelo o que o enunciado pede
int ValidaN(int N){
	int a=0;
	while(a==0){
		scanf("%d",&N);
		if (0<N && 1001>N)  //Caso 1<=N<=10^3, sai do laco
			return N;
		else
			printf("Valor invalido de N.Inserir valor 1<=N<=10^3 \n");
	}	
}

//Funcao para validar o M pelo o que o enunciado pede
int ValidaM(int M){
	int a=0;
	while(a==0){
	scanf("%d",&M);
		if (0<M && 11>M)  //Caso 1<=M<=10, sai do laco
			return M;
		else
			printf("Valor invalido de M. Inserir valor 1<=M<=10  \n");
	}	
}
	
//Funcao que ira inserir uma pessoa na lista de Entrada ja de maneira ordenada. Esta prioriza o T e depois o I.
void InsereOrdenadoLista(fila** head,int I, int T, int D){
	struct fila* novo = (struct fila*)malloc(sizeof(struct fila));
	novo->I = I;
	novo->T = T;
	novo->D = D;
	novo->prox = NULL;
	
	struct fila* aux;
	struct fila* auxAnt;
	aux = *head;
	auxAnt = *head;
	//Caso a Lista esteja vazia ou o novo tenha o menor T da lista
	if (*head == NULL || (*head)->T >= novo->T){
		novo->prox = *head;
		*head = novo;
	}
	//Caso o novo nao seja o menor valor de T, ira percorrer ate encontrar um T maior
	else{
		while (aux->prox != NULL && aux->prox->T < novo->T) {
			auxAnt = aux;
			aux = aux->prox;
		}
		//Neste caso, o novo tem o maior T
		if(aux->prox == NULL){
			novo->prox = aux->prox;
			aux->prox = novo;	
		}
		//Caso o novo for idoso, ele tera preferencia e ja pode ser inserido
		else if(novo->I > 64){
			novo->prox = aux->prox;
			aux->prox = novo;	
		}
		//Caso o novo nao for idoso, ira checar se tem idosos neste T. Se nao tiver, vai so adicionar aqui
		else{
			if(aux->I >64){	
				//Ira percorrer ate acabar os idosos neste T
				while(aux->I > 64){
					auxAnt->prox = aux;	
					aux = aux->prox;
				}
			}
			novo->prox = aux->prox;
			aux->prox = novo;
		}
	}
}

//Funcao para imprimir a fila desejada
void ImprimeFila(fila* head){
	if (head == NULL)
		printf("NULL");
	fila* aux = head;
	while(aux != NULL){
		printf("%d ",aux->I);
		aux = aux->prox;
	}
	printf("\n");
}

//Funcao que ia fazer a validacao de I, T e D exigido pelo enunciado e chamar a funcao InsereOrdenadoLista
struct fila *ValidaITD(fila* head,int N){
	int cont=0,I,T,D,a=0;
	while (cont != N){
		
		scanf("%d",&I);
		if(I <10 || I>90){
			a=0;
			while(a==0){
				printf("Valor invalido de I, inserir um valor 10 <= I <= 90.\n");
				scanf("%d",&I);
				if (9<I && 91>I)
					a=1;				
			}
		}
		
		scanf("%d",&T);
		if(T <0 || I>840){
			a=0;
			while(a==0){
				printf("Valor invalido de T, inserir um valor 0 <= T <= 840.\n");
				scanf("%d",&T);
				if (-1<T && 840>T)
					a=1;				
			}
		}
		
		scanf("%d",&D);
		if (D<2 || D >10){
			a=0;
			while(a==0){
				printf("Valor invalido de D, inserir um valor 2 <= D <= 10.\n");
				scanf("%d",&D);
				if (1<D && 11>D)
					a=1;				
			}
		}
		
		cont++;
		InsereOrdenadoLista(&head,I,T,D);
	}
	return head;
}
//Funcao que ira inserir uma pessoa na lista de Espera ja de maneira ordenada. Esta prioriza apenas o I.
void InsereOrdenadoListaEspera(fila** head,int I, int T, int D){
	struct fila* novo = (struct fila*)malloc(sizeof(struct fila));
	novo->I = I;
	novo->T = T;
	novo->D = D;
	novo->prox = NULL;
	
	struct fila* aux;
	struct fila* auxAnt;
	aux = *head;
	auxAnt = *head;
	//Caso a Lista esteja vazia ou o novo eh o mais idoso
	if (*head == NULL || (*head)->T >= novo->T){
		novo->prox = *head;
		*head = novo;
	}
	
	//Caso o novo seja idoso
	else if (novo->I > 64){
		//Se for o primeiro idoso ou o mais idoso da lista de espera
		if ((*head)->I <65 || (*head)->T <= novo->T){
			novo->prox = *head;
			*head = novo;	
		}
		//Se nao for o primeiro idoso nem o mais idoso da lista de espera	
		else{
			
			//Ira percorrer ate acabar os idosos ou um idoso com T maior aparecer
			while (aux->prox->I > 64 && aux->I < novo->I) 
				aux = aux->prox;
			novo->prox = aux->prox;
			aux->prox = novo;
		}
	}
	
	//Caso o novo nao seja idoso
	else{
		//Ira percorrer ate acabar os idosos ou a lista.
		while (aux->I > 64 && aux->prox != NULL){
			auxAnt = aux;
			aux = aux->prox;
		}
		//Uma vez que percorreu, ira checar se o menor T dos nao-idosos e maior que o novo
		if(aux->T >= novo->T){
			novo->prox = aux->prox;
			auxAnt->prox = novo;	
		}
		//Caso o T do novo for maior que o menor T nao-idoso, ira percorrer ate encontrar o lugar apropriado
		else{
			while (aux->prox != NULL && aux->prox->T < novo->T) 
				aux = aux->prox;
			novo->prox = aux->prox;
			aux->prox = novo;	
		}
	}
}


//Funcao que Remove uma pessoa da lista, necessario para tirar alguem da Espera ao ser atendido
int RemoveFila(fila* head){
	struct fila* aux = (struct fila*)malloc(sizeof(struct fila));
	aux=head;
	if(aux==NULL || aux->prox == NULL) 
		return NULL;
	else
		return aux->prox;
}
//Funcao que ira gerenciar a lista de Entrada com os caixas, inserir e imprimir quando necessario.
void ControleCaixa(struct fila* headEntrada, struct fila* headEspera,int *vetorCaixas,int M){
	fila* auxEntrada = headEntrada;
	int i,nova=0;
	while(auxEntrada != NULL){
		//Primeiro ira checar se existe alguem na lista de espera. Caso sim,ira checar se alguem saiu antes ou durante o instante T
		for(i=0;i<M;i++){
			if(headEspera != NULL){
				//Neste caso, haviam pessoas na fila de Espera,elas entraram no caixa no instante apropriado e sairam da fila de espera
				if(vetorCaixas[i] <= auxEntrada->T && vetorCaixas[i] != 0){
					vetorCaixas[i] += headEspera->D;
					headEspera = RemoveFila(headEspera);
				}
				if(vetorCaixas[i] <= auxEntrada->T)
					vetorCaixas[i] = 0;			
			}
			//Neste caso, nao haviam pessoas na fila de Espera mas o caixa foi liberado
			else{
				if(vetorCaixas[i] <= auxEntrada->T)
					vetorCaixas[i] = 0;
			}			
		}	
		i=0;
		
		//Agora ira checar se existe algum caixa disponivel no momento que uma nova pessoa chega. 
		//Caso sim, sera atendida no caixa. Caso nao, entrara na fila de espera. 
		while(i != M && nova == 0){
			//Este caixa esta vazio
			if(vetorCaixas[i] == 0){
				vetorCaixas[i] = auxEntrada->D + auxEntrada->T;
				nova=1;
			}
			//Caixa nao vazio, checara o prox
			else
				i++;
		}
		//Se a nova pessoa nao entrou no Caixa ao chegar, ela entrara na fila de espera
		if (nova == 0)
			InsereOrdenadoListaEspera(&headEspera,auxEntrada->I,auxEntrada->T,auxEntrada->D);
		
		nova=0;
		//Ira checar se e apropriado printar a fila de espera agora
		if(auxEntrada->prox != NULL && auxEntrada->T != auxEntrada->prox->T)
			ImprimeFila(headEspera);

		auxEntrada = auxEntrada->prox;		
	}
	ImprimeFila(headEspera);
}

int main(){
	
	int N,M,i;
	//Funcoes que irao validar o valor de N e M como especificado no enunciado.
	N=ValidaN(N);
	M=ValidaM(M);
	//Criando o vetorCaixas que ira armazenar caixas ocupados. 0 Significa vazio
	int vetorCaixas[M];	
	for(i=0;i<M;i++)
		vetorCaixas[i] = 0;
	
	//Criacao do ponteiro de fila para entrada de dados
	struct fila* headEntrada = (struct fila*)malloc(sizeof(struct fila));
	headEntrada  = NULL;
	//Criando uma fila com os dados de entrada do usuario
	headEntrada  = ValidaITD(headEntrada,N);
	
	//Criacao do ponteiro de fila para Controle, ou seja, o que sera printado
	struct fila* headEspera = (struct fila*)malloc(sizeof(struct fila));
	headEspera  = NULL;
	//Iniciando o processo de fluxo de caixa
	ControleCaixa(headEntrada,headEspera,vetorCaixas,M);
	
	
	return 0;
}

