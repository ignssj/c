// Pesquisa e Classificação de Dados – Trabalho 01 - 02/08/2021
// Ignacio Pineiro Garcia (ignaciogarcia.aluno@unipampa.edu.br)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <sysinfoapi.h>

char Linha[100];
FILE *arq;
int N;

void leArquivo(int *vet) {
	arq = fopen("entrada.txt", "r");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
	}
	int i=0;
	while (!feof(arq)) {
		fgets(Linha,100, arq);
		vet[i]=atoi(Linha);
		i++;
	}
	fclose(arq);
}

void gravaEntrada(int *vet) {
	int i;
	arq = fopen("entrada.txt", "w");
	if (arq == NULL) {
		printf("Problemas ao criar o arquivo\n");
		return;
	}
	for(i=0; i<N; i++) {
		fprintf(arq,"%d\n",vet[i]);
	}
	fclose(arq);
}

void escreveArquivo(char *metodo, int *vet) {
	int i;
	arq = fopen(metodo, "w");
	if (arq == NULL) {
		printf("Problemas ao criar o arquivo\n");
		return;
	}
	for(i=0; i<N; i++) {
		fprintf(arq,"[%d]",vet[i]);
	}
	fclose(arq);
}

void preencheVetor(int *vet) {
	srand(time(NULL));
	int i;
	for(i=0; i<N; i++) {
		vet[i] = rand();
	}
}

void printaVetor(int *vetor) {
	int i;
	printf("[");
	for(i=0; i<(N-1); i++) {
		printf("%i, ",vetor[i]);
	}
	printf("%i]\n",vetor[i]);
}

void insertionSort(int *vet) {
	int i,j,temp,sig=0;
	for(i=1; i<=(N-1); i++) {
		temp = vet[i];
		for(j=(i-1); j>=0; j--) {
			if(vet[j] > temp) {
				vet[j+1] = vet[j];
				sig=1;
			} else
				break;
		}
		if(sig) {
			vet[j+1] = temp;
		}
	}
}

void shellSort(int *vet) {
	int tst,i,j,mtd;
	for(mtd = 1; mtd < N; mtd = 3*mtd+1);
	while(mtd > 0) {
		mtd = (mtd-1)/3;
		for(i = mtd; i < N; i++) {
			tst = vet[i];
			j = i;
			while(vet[j - mtd] > tst) {
				vet[j] = vet[j - mtd];
				j -= mtd;
				if(j < mtd) break;
			}
			vet[j] = tst;
		}
	}
}

void quickSort(int *vet, int esq, int dir) {
	int i = esq;
	int j = dir;
	int x = vet[(esq + dir) / 2];
	int y;
	while(i <= j) {
		while(vet[i] < x && i < dir) {
			i++;
		}
		while(vet[j] > x && j > esq) {
			j--;
		}
		if(i <= j) {
			y = vet[i];
			vet[i] = vet[j];
			vet[j] = y;
			i++;
			j--;
		}
	}
	if(j > esq) {
		quickSort(vet, esq, j);
	}
	if(i < dir) {
		quickSort(vet, i, dir);
	}
}


int main() {
	long long int inicio;
	long long int end;
	clock_t tic,toc;
	double spentI=0.0;
	double spentS=0.0;
	double spentQ=0.0;
	printf("BEM VINDO!\nInforme o tamanho do vetor...\n");
	scanf("%i",&N);
	system("cls");
	int vet[N];
	preencheVetor(vet);
	gravaEntrada(vet);
	int op=0,i;
	do {
		op=0;
		while(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7) {
			leArquivo(vet);
			printf("*************** MENU ***************\n1- Insertion Sort\n2- Shell Sort\n3- Quick Sort\n4- Ultimos tempos registrados\n5- Vetor Ordenado\n6- Mostrar entrada\n7- Sair\n************************************\n");
			scanf("%i",&op);
			system("cls");
		}
		switch(op) {
			case 1:
				tic = clock();
				insertionSort(vet);
				toc = clock();
				spentI=(double)(toc-tic)/CLOCKS_PER_SEC;
				escreveArquivo("insertion.txt",vet);
				break;
			case 2:
				tic = clock();
				shellSort(vet);
				toc = clock();
				escreveArquivo("shellsort.txt",vet);
				spentS=(double)(toc-tic)/CLOCKS_PER_SEC;
				break;
			case 3:
				tic = clock();
				quickSort(vet,0,N-1);
				toc = clock();
				spentQ=(double)(toc-tic)/CLOCKS_PER_SEC;
				escreveArquivo("quicksort.txt",vet);
				break;
			case 4:
				printf("Insertion-> %f seconds.\nShell-> %f seconds.\nQuick-> %f seconds.\n", spentI,spentS,spentQ);
				system("pause");
				break;
			case 5:
				quickSort(vet,0,N-1);
				printf("**Vetor Ordenado**\n");
				printaVetor(vet);
				system("pause");
				break;
			case 6:
				printf("**Vetor de Entrada**\n");
				printaVetor(vet);
				system("pause");
				break;
			case 7:
				exit(1);
				break;
			default:
				printf("Opçao invalida.\n");
		}
		printf("\n");
		system("cls");
	} while(true);
	return 0;
}
