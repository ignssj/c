// Pesquisa e Classificação de Dados – Trabalho 02
// 20/09/2021
// Ignacio Pineiro Garcia (ignaciogarcia.aluno@unipampa.edu.br)

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct lista {
 int codigo;
 char descricao[30];
 float valor;
 struct lista* prox;
};
typedef struct lista Lista;

Lista* hashTable[101];
double FC;

Lista* inicializa (void){
 return NULL;
}

int vazia (Lista* l){
 if (l == NULL)
 return 1;
 else
 return 0;
}

bool Bbusca (Lista* l, int v){
 Lista* p;
 for (p=l; p!=NULL; p=p->prox){
 if (p->codigo == v){
 return true;
}}
 return false;
}

void Vbusca (Lista* l, int v){
 Lista* p;
 system("cls");
 for (p=l; p!=NULL; p=p->prox){
 if (p->codigo == v){
 printf("Codigo: %i\nValor: %f\nDescricao: %s\n",p->codigo,p->valor,p->descricao);
 return;
}}
 printf("Valor inexistente na tabela.\n");
}

Lista* cria (int v)
{
 Lista* p = (Lista*) malloc(sizeof(Lista));
 p->codigo = v;
 printf("Informe o valor...\n");
 scanf("%f",&p->valor);
 printf("Insira uma descricao... (Sem Espacos)\n");
 scanf("%s",p->descricao);
 return p;
}

Lista* insere_ordenado (Lista* l, int cod){
 if(Bbusca(l,cod)){
 	printf("ERRO - Codigo presente na tabela.\n");
 	return l;
 }
 Lista* novo = cria(cod); 
 Lista* ant = NULL; 
 Lista* p = l; 
 while (p != NULL && p->codigo < cod) {
 ant = p;
 p = p->prox;
 } if (ant == NULL) { 
 novo->prox = l;
 l = novo;
 } else { 
 novo->prox = ant->prox;
 ant->prox = novo;
 }
 return l;
}

void imprime_rec (Lista* l){
 if (vazia(l)){
 printf("NULL\n");
 return;
}
 printf("%d->",l->codigo);
 imprime_rec(l->prox);
}

void libera (Lista* l){
 Lista* p = l;
 while (p != NULL) {
 Lista* t = p->prox; 
 free(p);
 p = t; 
 }
}

void imprimeHash(int N){
for(int i=0;i<=N;i++){
		printf("\nPosicao...: [%i]: ",i);
		imprime_rec(hashTable[i]);
	}
}

void inicializaHash(){
	for(int i=0;i<=101;i++){
		hashTable[i] = inicializa();
	}
}

void insereHT(){
	int aux,cinterno;
	printf("Informe o codigo\n");
	scanf("%i",&cinterno);
	aux = cinterno % 101;
	printf("[%d]\n",aux);
	hashTable[aux] = insere_ordenado(hashTable[aux], cinterno);
	if(vazia(hashTable[aux])){
		printf("Lista vazia...\n");
		return;
	}
}

void chamadaInsercao(int x){
	for(int i=0; i<x; i++){
				insereHT();
			}
}

void procuraHT(){
	int cod,aux;
	printf("Insira o codigo do registro...\n");
	scanf("%i",&cod);
	aux = cod % 101;
	Vbusca(hashTable[aux],cod);
}

void liberaHash(Lista *l){
 if (!vazia(l))
 {
 liberaHash(l->prox);
 free(l);
 }
}

int main (void) {
	int op,i,n;
	int inseridos=0;
	inicializaHash();
	system("cls");
	while(true){
	printf("------------------------- MENU -------------------------\n");
	printf("1- Inserir elementos\n2- Consultar Hash Table\n3- Exibir Hash Table\n4- Encerrar\n");
	scanf("%i",&op);
	system("cls");
	switch(op){
		case 1:
			printf("Informe o numero de elementos a serem inseridos...\n");
			scanf("%d",&n);
			inseridos = inseridos + n;
			chamadaInsercao(n);
			break;
			case 2:
				procuraHT();
				system("pause");
				break;
				case 3:
					imprimeHash(101);
					FC = double(inseridos)/101;
					printf("\nFator de carga........: %lf\n\n",FC);
					system("pause");
					break;
					case 4:
						for(int i=0;i<101;i++){liberaHash(hashTable[i]);}
						printf("Hash liberada!\nEncerrando");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".");
						return 1;
						break;
						default:
							printf("ERRO - Entrada invalida.\n");
							break;	
	}
	system("cls");
}
}
