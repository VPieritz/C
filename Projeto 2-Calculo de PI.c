//Projeto para calcular PI, até P casas.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Transformando pi em decimal para comparar ate a p-esima casa
double calculoDecimal(int P,double pi){
  	double piaux,fractpart, intpart;
	int i;
	//Ate a pesima casa, ira multiplicar por 10,separar a parte inteira da fracao e retornar a parte inteira.
	//O for e necessario pois P>13 quebrava o piaux
  	for(i=0;i<P;i++){
   		pi *= 10;
   		fractpart = modf(pi, &intpart);//Vai sempre tirar a parte inteira
  		piaux= floor(intpart);//vai arredondar para dar certo o calculo da parte inteira
   }   
    return piaux;
}
//Calcula auxa
double termoA(double j,double aux){
	aux *= ((j-1)/j);
	return aux;
}
//Calcula 1/n
double termoB(double i,double aux){
	double n; 
	n =(2*i)-1;
	aux = 1/n;
	return aux;
}
//calcula pow(1/2,n)
double termoC(double i, double pi){
	double n;
	n =(2*i)-1;
	pi = pow(0.5,n);
	return pi;
}

double CalculoPi(int P){
	int cont=0;
	double i=2,j=0,pi=1,ant=0.5,piaux=0,piaux2=0;
	double auxa=1,auxb=1;
	
	//Enquanto nao contar 3 vezes pi igual, ira continuar iteracao 
	//pn = ant + [(auxa) * 1/n * pow(1/2,n)]
	//Outra forma de escrever: pi = ant + [termoA * termoB * TermoC]
	while(cont <3){
		j+= 2;
		auxa = termoA(j,auxa);
		pi=auxa;
		auxb = termoB(i,pi);
		pi *= auxb;			
		pi *= termoC(i,pi);
		//printf ("Pi depois do termoC:%.*f\n", (P), pi);
        //Finaliza somando com anterior
        pi += ant;
        //anterior se transforma em pi para a proxima interacao
        ant= pi;
        pi *=6;
		//Aqui ira multiplicar pi por 10^p, para comparar, entre piaux(pi atual) e piaux2(pi anterior), se os numeros ate a p-esima casa sao iguais.
		piaux= calculoDecimal(P,pi);
		if(piaux2 == piaux)
			cont++;
		else{
			cont=0;
			piaux2=piaux;
		}	
		i++;	
	}   
	return pi;
}


int main (){
	int P, a=0;
	double pi;
	
	//Laco que obriga o usuario a colocar o valor adequado de P
	while(a==0){
		printf("Digite o valor de P, tal que 1<=P<=15\n");
		scanf("%d",&P);
		if (0<P && 16>P)  //Caso 1<=P<=15, sai do laco
			a=1;
		else
			printf("Valor invalido de P. \n");
	}
	pi=CalculoPi(P);
    printf ("\n\n\nRESULTADO FINAL: %.*f\n", (P),pi);
    printf("Valor de P:%d",P);
	return 0;
}


