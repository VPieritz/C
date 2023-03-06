#include <stdio.h>
#include <stdlib.h>

/**********************************************************************/
/* Nome: Vitor Oliveira Pieritz                                       */                                             */
/* Programa de biblioteca de livros em AVL                            */
/* Compilador: Dev-C++ versão 5.11                                    */
/**********************************************************************/

//Struct para AVL, sera usada para armazenar informacoes dos livros.
typedef struct AVL{
	int id, ed,altd,alte,retirar;
	char usuario[30],nomelivro[30],nomeautor[30],editora[30];
	struct AVL *esq,*dir;
}AVL;

//Struct para a criacao de uma lista, usada para armazenar usuarios.
typedef struct lista{
	int id;
	char nome[30];
	struct lista *prox;
}lista;

//Função que sera chamada caso o balanceamento exigir
AVL* rotacaoesquerda(AVL *aux){
	AVL *aux1, *aux2;
	aux1= aux->dir;
	aux2 = aux1->esq;
	aux->dir = aux2;
	aux1->esq= aux;
	
	if(aux->dir == NULL)
		aux->altd=0;
	else if (aux->dir->alte > aux->dir->altd)
		aux->altd = aux->dir->alte+1;
	else
		aux->altd= aux->dir->altd+1;
	
	if(aux1->esq->alte > aux1->esq->altd)
		aux1->alte = aux1->esq->alte+1;	
	else
		aux1->alte = aux1->esq->altd+1;
	
	return aux1;		
}

//Função que sera chamada caso o balanceamento exigir
AVL* rotacaodireita(AVL *aux){
	AVL *aux1, *aux2;
	aux1= aux->esq;
	aux2 = aux1->dir;
	aux->esq = aux2;
	aux1->dir= aux;
	
	if(aux->esq == NULL)
		aux->alte=0;
	else if (aux->esq->alte > aux->esq->altd)
		aux->alte = aux->esq->alte+1;
	else
		aux->alte= aux->esq->altd+1;
	
	if(aux1->dir->alte > aux1->dir->altd)
		aux1->altd = aux1->dir->alte+1;	
	else
		aux1->altd = aux1->dir->altd+1;
	
	return aux1;		
}

//Funcao que garantira que a arvore avl nao fique desequilibrada, garantindo integra sua caracteristica de AVL.
AVL *balanceamento (AVL *aux){
	//Funcao que ira balancear a arvore avl caso ela esteja desequilibrada, ou seja, a diferenca entre um dos lados seja = 2 ou = -2.
	//Nao ha necessidade de pensar em uma diferenca maior que 2 ou menos que -2 pois esta funcao sempre sera executada durante a insercao de elemento, impedindo uma diferenca maior que estas.
	
	int dif, difaux;//dif e a variavel da subtracao da altura do lado direita pelo esquerda. difaux e uma variavel auxiliar que ira descer um de altura para checar o quanto que precisa descer na arvore para ela ser balanceada.
	dif= aux->altd - aux->alte;
	if( dif==2 ){
		difaux = aux->dir->altd - aux->dir->alte;
		if (difaux >=0)
			aux = rotacaoesquerda(aux);
			else{
				aux->dir=rotacaodireita(aux->dir);
				aux=rotacaoesquerda(aux);
			}
	}
	else if (dif == -2){
		difaux= aux->esq->altd - aux->esq->alte;
		if (dif <= 0)
			aux=rotacaodireita(aux);
		else{
			aux->esq = rotacaoesquerda(aux->esq);
			aux=rotacaodireita(aux);
		}
	}
	return aux;
}

//Funcao que ira inserir novos nos na arvore, ou seja, adicionara livro a biblioteca
AVL *INSERE(AVL *aux){
	int id, ed;
	AVL *novo;

	//Lista vazia. Ira criar a partir de um novo.
	if (aux == NULL){
		novo = (AVL*) malloc (sizeof(AVL));
		char auxusuario= "Nenhum";
		puts("Digite na ordem:\nO nome do livro.\nO nome do autor do livro.\nO nome da editora do livro.\n\n");
		fflush(stdin);
		fgets(novo->nomelivro,sizeof(novo->nomelivro),stdin);
		fflush(stdin);
		fgets(novo->nomeautor,sizeof(novo->nomeautor),stdin);
		fflush(stdin);
		fgets(novo->editora,sizeof(novo->editora),stdin);
		fflush(stdin);
		puts("\nDigite na ordem:\nO ID do livro:\nA edicao do livro:\n");
		scanf("%d %d",&id,&ed);
		novo->id=id;
		novo->ed=ed;
		novo->altd=0;
		novo->alte=0;
		novo->retirar=0;
		novo->esq=NULL;
		novo->dir=NULL;
		strcpy(novo->usuario,"Nenhum");
		aux=novo;
	}
	//Nesse caso, a arvore nao esta vazia, entao ela sera inserida no local apropriado.
	else{
		if (id< aux->id){
			aux->esq=INSERE(aux->esq);//Ira descer um de altura na arvore, a fim de inserir o livro no local adequado
			if(aux->esq->altd > aux->esq->alte)
				aux->alte= aux->esq->altd +1;
			else
				aux->alte=aux->esq->alte +1;
			aux=balanceamento(aux);	
			
		}
		
		else{
			aux->dir=INSERE(aux->dir);//Ira descer um de altura na arvore, a fim de inserir o livro no local adequado
			if(aux->dir->altd > aux->dir->alte)
				aux->altd = aux->dir->altd +1;
			else
				aux->altd=aux->dir->alte +1;	
			aux=balanceamento(aux);
			
		}
	}
	return aux;
}

//Funcao que ira imprimir a arvore AVL em Ordem: Esquerda, raiz e direita.
void listarordem(AVL *aux){
	if (aux != NULL){
		listarordem(aux->esq);
		fprintf(stdout,"\n\nLivro:%sID do livro retirado:%d \nNome do autor do livro:%sNome da editora:%sEdicao:%d,\nUsuario que retirou o livro:%s\n", aux->nomelivro,aux->ed,aux->nomeautor,aux->editora,aux->id,aux->usuario);
		listarordem(aux->dir);
	}
}

//Funcao que ira imprimir a arvore AVL em Pré-Ordem:Raiz,esquerda e direita.
void listarpreordem(AVL *aux){
	if (aux != NULL){
		fprintf(stdout,"\n\nLivro:%sID do livro retirado:%d \nNome do autor do livro:%sNome da editora:%sEdicao:%d,\nUsuario que retirou o livro:%s\n", aux->nomelivro,aux->ed,aux->nomeautor,aux->editora,aux->id,aux->usuario);
		listarpreordem(aux->esq);
		listarpreordem(aux->dir);
	}
}

//Funcao que ira imprimir a arvore AVL em Pós-Ordem:Esquerda, direita e raiz.	
void listarposordem(AVL *aux){
	if (aux != NULL){
		listarposordem(aux->esq);
		listarposordem(aux->dir);
		fprintf(stdout,"\n\nLivro:%sID do livro retirado:%d \nNome do autor do livro:%sNome da editora:%sEdicao:%d,\nUsuario que retirou o livro:%s\n", aux->nomelivro,aux->ed,aux->nomeautor,aux->editora,aux->id,aux->usuario);
	}
}

//Funcao que ira remover um no a partir da id inserida pelo usuario do programa.
AVL *REMOVER(AVL *aux, int id){
	AVL *p, *p2;
	
	if (aux->id == id){
		//Caso o livro a ser removido nao tenha filhos
		if(aux->esq == aux->dir){
			aux->id = NULL;
			aux->ed= NULL;
			aux->retirar =NULL;
			aux->altd =NULL;
			aux->alte =NULL;
			aux->dir =NULL;
			aux->esq =NULL;
			return NULL;			
		}
		//Caso o livro a ser removido nao tenha filhos para a esquerda
		else if(aux->esq == NULL){
			p=aux->dir;
			aux->id = NULL;
			aux->ed= NULL;
			aux->retirar =NULL;
			aux->altd =NULL;
			aux->alte =NULL;
			aux->dir =NULL;
			aux->esq =NULL;
			return p;
		}
		//caso o livro a ser removido nao tenha filhos para a direita
		else if(aux->dir == NULL){
			p=aux->esq;
			aux->id = NULL;
			aux->ed= NULL;
			aux->retirar =NULL;
			aux->altd =NULL;
			aux->alte =NULL;
			aux->dir =NULL;
			aux->esq =NULL;
			return p;
		}
		//caso o livro a ser removido tenha filhos para ambos os lados.
		else{
			p2=aux->dir;
			p=aux->dir;
			while(p->esq != NULL){
				p=p->esq;
			}
			p->esq= aux->esq;
			aux->id = NULL;
			aux->ed= NULL;
			aux->retirar =NULL;
			aux->altd =NULL;
			aux->alte =NULL;
			aux->dir =NULL;
			aux->esq =NULL;
			return p2;
		}
	}
	else if (aux->id < id)
		aux->dir = REMOVER(aux->dir,id);
	else
		aux->esq = REMOVER(aux->esq,id);
	return aux;
}

//Uma vez removido o no da arvore, e necessario atualizar a arvore AVL.
AVL *ATUALIZA (AVL *aux){
	if(aux != NULL){
		aux->esq= ATUALIZA(aux->esq);
		if (aux->esq ==NULL)
			aux->alte=0;
		else if (aux->esq->alte > aux->esq->altd)
			aux->alte= aux->esq->alte +1;
		else
			aux->alte = aux->esq->altd +1;	
		aux->dir = ATUALIZA(aux->dir);
		if(aux->dir == NULL)
			aux->altd = 0;
		else if(aux->dir->alte > aux->dir->altd)
			aux->altd = aux->dir->alte +1;
		else
			aux->altd = aux->dir->altd +1;
		aux=balanceamento (aux);
	}
	return aux;
}

//Funcao que ira consultar se o livro existe na arvore AVL.
int CONSULTAR(AVL *aux, int id, int achou){
	if (aux != NULL && achou==0){
		if( aux->id == id){
			achou=1;
			printf("Livro encontrado!\n");
			fprintf(stdout,"Livro:%sID do livro retirado:%d\nNome do autor do livro:%sNome da editora:%sEdicao:%d,\nUsuario que retirou o livro:%s\n", aux->nomelivro,aux->ed,aux->nomeautor,aux->editora,aux->id,aux->usuario);
		}
		else if(id< aux->id)
			achou= CONSULTAR(aux->esq,id,achou);
		else
			achou=CONSULTAR(aux->dir, id, achou);
	}
	return achou;
}

//Funcao que ira adicionar um no na lista de usuarios.
lista *INSERIRusuario(lista *aux){
	lista *novo;
	novo = (lista*) malloc (sizeof(lista));
	puts("Digite o nome do Usuario a ser inserido.\n");
	fflush(stdin);
	fscanf(stdin, "%s", novo->nome);
	fflush(stdin);
	novo-> prox = aux;
	novo->id=0;//Significa que o usuario nao possui livros retirados.
	return novo;
}

//Funcao que ira imprimir a lista de usuarios.
void imprimeusuarios(lista *aux){

	while(aux!= NULL){       
		fprintf(stdout,"Usuario:%s \nID do livro retirado:%d \n\n", aux->nome,aux->id);
		aux=aux->prox;
	}
}

//Funcao que ira consultar se existe um usuario com os caracteres digitados pelo usuario do programa
int CONSULTARusuario(lista *aux, char *auxusuario,int consultarusuario,int id){
	while(aux!= NULL && consultarusuario !=0 ){ 
		if (strcmp(auxusuario,aux->nome) == 0){//O 0 significa que as strings sao iguais, dessa forma, redefinimos a variavel para 0 a fim de sair do laco e informar isto para a main.
			consultarusuario =0;
			aux->id= id;
		}
		else{
			aux=aux->prox;
		}
	}
	return consultarusuario;
}

//Funcao que permitira registrar se o livro for retirado por um usuario.
int RETIRAR (AVL *aux, int id,int achou,char *usuario){//Basicamente e uma funcao de consultar, mas que tambem ira modificar a variavel retirado e usuario da struct dos livros.
	if (aux != NULL && achou==0){
		if( aux->id == id){
			achou=1;
			aux->retirar=1;
			strcpy(aux->usuario,usuario);
		}
		else if(id< aux->id)
			achou= RETIRAR(aux->esq,id,achou,usuario);
		else
			achou=RETIRAR(aux->dir, id, achou,usuario);
	}
	return achou;
}

//Funcao que imprimira apenas os livros que foram retirados por algum usuario.
void livrosretirados(AVL *aux){//Basicamente um listar em ordem, mas com um if para imprimir apenas se a variavel retirar=1.
	if (aux != NULL){
		livrosretirados(aux->esq);
		if (aux->retirar==1)
			fprintf(stdout,"Livro:%sID do livro retirado:%d\nNome do autor do livro:%sNome da editora:%sEdicao:%d,\nUsuario que retirou o livro:%s\n", aux->nomelivro,aux->ed,aux->nomeautor,aux->editora,aux->id,aux->usuario);
		livrosretirados(aux->dir);
	}
}

int main (int argc, char *argv[]){

	//Criando a raiz da arvore avl, inicialmente nula.
	AVL *raiz=NULL;
	
	//Criando o inicio da lista de usuario.
	lista *INICIO=NULL;
	
	//variaveis necessarias para o menu do exercicio;
	int op=1, id, opc,listar,consultar,achou=0,deletar,consultarusuario,auxretirar;
	char auxusuario[30];
	
	//Menu principal que dara as possibilidades para utilizar a biblioteca.
	while(op!=0){
		
		system("cls");
		puts("BEM VINDO A BIBLIOTECA DE ESTRUTURA DE DADOS. \n");
		puts("Digite a opcao desejada.\n");
		puts("1-Inserir um novo usuario.\n");
		puts("2-Inserir um novo livro.\n");
		puts("3-Consultar alguma informacao da biblioteca.\n");
		puts("4-Retirar um livro.\n");
		puts("5-Listar todos os livros da biblioteca\n");
		puts("6-Deletar um livro da biblioteca\n");
		puts("0-Sair do programa.\n");
		puts("Digite sua opcao:\n");
		scanf("%d",&opc);
		switch(opc){
			
			//Inserir usuario na lista de usuario.
			case 1:
				INICIO=INSERIRusuario(INICIO);
				puts("Usuario inserido com sucesso!");
				system("pause");
				break;
				
			//Inserir um novo no(livro) na arvore AVL).
			case 2:;
				raiz= INSERE(raiz);
				puts("Livro inserido com sucesso!\n");
				system("pause");
				break;
			
			//Consultar alguma info da biblioteca.
			case 3:
				
				puts("Digite como deseja consultar o livro:\n1-Se o livro existe na biblioteca e mostrar suas infos\n2-Usuarios desta biblioteca e suas informacoes.\n3-Livros que estao alocados.\n");
				scanf("%d",&consultar);
			
				//Caso o usuario queira consultar se existe algum livro na biblioteca.
				if (consultar ==1){
					if (raiz == NULL)
						puts("Arvore vazia. Retornando ao menu.\n");
					else{
					puts("Agora digite o ID do livro buscado.");
					scanf("%d",&id);
					achou=0;
					achou = CONSULTAR(raiz,id,achou);
					
					if(achou==0)
						puts("Livro nao encontrado! Retornando ao menu.\n");					
					}		
				}
				
				//Caso queira-se imprimir apenas as informacoes dos usuarios cadastrados.
				else if (consultar ==2 ){
					if (INICIO==NULL)
						puts("Nao ha usuarios cadastrados nesta biblioteca.\n");
					else{
						puts("Lista de usuarios da biblioteca:\n\n");
						imprimeusuarios(INICIO);	
					}
				}
				
				//Caso queira imprimir apenas os livros retirados.
				else if(consultar == 3)
					livrosretirados(raiz);

				//Condicao caso o usuario nao tenha escolhido a opcao correta para consultar.
				else 
					puts("Opcao invalida, retornando ao menu.\n");
				system("pause");
				break;
				
			//Retirar um livro.
			case 4:
				//Caso a bibliteca estiver vazia, nem vai entrar no algoritmo.
				if(raiz==NULL)
					puts("A biblioteca esta vazia. Nao ha livros para ser listados.\n");
					
				//Caso a biblioteca nao esteja vazia, vai checar se a lista de usuarios nao esta vazia
				else{
					
					if(INICIO==NULL)
						puts("Nao ha usuarios para retirar algum livro. Retornando ao menu.\n");
					//Se nem a biblioteca nem a lista de usuarios estiver vazia, vai procurar se o livro existe.
					else{	
						puts("Agora digite o ID do livro a ser procurado.");
						scanf("%d",&id);
						achou=0;
						achou = CONSULTAR(raiz,id,achou);
						//Se nao encontrar o livro, saira para o menu.
						if(achou==0)
							puts("Livro nao encontrado! Retornando ao menu.\n");	
						//Agora vai procurar se o usuario que ira retirar o livro existe. Se ele existir, ja vai registrar o id do livro no usuario.			
						else{
							puts("znDigite o Usuario que ira retirar o livro.\n");
							fflush(stdin);
							fscanf(stdin, "%s", auxusuario);
							fflush(stdin);
							consultarusuario = 1;//Necessario para entrar no loop a primeira vez na funcao CONSULTARusuario.
							consultarusuario=CONSULTARusuario(INICIO,auxusuario,consultarusuario,id);
							//Caso haja biblioteca, haja lista de usuarios, o livro existe na biblioteca e o usuario tambem, ira fazer o processo de retirar o livro.
							if (consultarusuario == 0){
								achou=0;
								auxretirar= RETIRAR(raiz, id,achou, auxusuario);
								//Se o livro for retirado com sucesso, ira apresentar para o usuario a informacao que foi um sucesso.
								if(auxretirar == 1)
									puts("Livro retirado com sucesso.\n");
								else
									puts("Nao houve sucesso ao retirar o livro.");
							}
							//Condicao caso o usuario do programa nao entre com um usuario existente na lista de usuarios
							else
								puts("Usuario nao encontrado. Voltando ao menu");
						}
					}
				}
				
				system("pause");
				break;
				
			//Listando todos os nos da arvore AVL.		
			case 5:
				//Opcao caso a biblioteca esteja vazia
				if(raiz==NULL)
					puts("A biblioteca esta vazia. Nao ha livros para ser listados.\n");
				
				//Se nao estiver vazia, ira dar as opcoes de listagem.
				else{
					puts("Digite como deseja que os livros sejam listados\n1-Ordem.\n2-Pre-Ordem.\n3-Pos-Ordem.\n");
					scanf("%d",&listar);
					if (listar == 1){
						puts("Listando os livros em ordem:\n");
						listarordem(raiz);
					}
					else if(listar == 2){
						puts("Listando os livros em pre-ordem:\n");
						listarpreordem(raiz);
					}
					else if(listar == 3){
						puts("Listando os livros em pos-ordem:\n");
						listarposordem(raiz);
					}
					else
						puts("Opcao invalida. Retornando para o menu da biblioteca.\n");
				}
				system("pause");
				break;			
				
			//Opcao de deletar algum nos da arvore AVL.
			case 6:
				
				//Caso a arvore esteja vazia
				if(raiz==NULL)
					puts("A biblioteca esta vazia. Nao ha livros para ser listados.\n");
				
				//Caso a arvore nao esteja vazia, vai receber um ID do usuario do programa, procurar se o no existe na arvore
				else{
						puts("Agora digite o ID do livro a ser deletado.");
						scanf("%d",&id);
						achou=0;
						achou = CONSULTAR(raiz,id,achou);
						//Livro nao encontrado
						if(achou==0)
							puts("Livro nao encontrado! Retornando ao menu.\n");	
						//Caso o livro seja encontrado, ira dar a opcao para o usuario se ele tem certeza de deletar o no.				
						else{
							puts("Ter certeza que deseja deletar o livro? Se sim, digite 1.\n");
							scanf("%d", &deletar);
							if(deletar == 1 ){
									raiz= REMOVER(raiz, id);
									raiz= ATUALIZA(raiz);
									puts("Livro deletado com sucesso da biblioteca.\n");
									deletar=0;
							}
							else
								puts("Livro nao sera deletado. Retornando ao menu.\n");
						}
				}
				system("pause");
				break;			
			
			//sair da biblioteca
			case 0:
			
			puts("Obrigado por utilizar a Biblioteca. Encerrando o programa");
			op = 0;
			break;
			
			//Caso usuario digite opcao invalida.
			default:
			
			puts("opcao invalida, reescolher a opcao.");
			system("pause");
			break;	
		}
	}
	return 0;	
}
