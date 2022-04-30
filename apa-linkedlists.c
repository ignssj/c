#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
   int valor;
   struct no *proximo;
} No;

void inserir_no_inicio(No **lista, int num) 
{
   No *novo = malloc(sizeof(No));   // 1 $$ 1 ## 1 /*t1*/ 
   novo->valor = num;       // 1 $$ 1 ## 1 /*t1*/ S
   novo->proximo = *lista;     // 1 $$ 1 ## 1 /*t1*/
   *lista = novo;           // 1 $$ 1 ## 1 /*t1*/ 
}

// procedimento para inserir no fim
void inserir_no_fim(No **lista, int num)
{
   No *aux, *novo = malloc(sizeof(No));

   if (novo)
   {
      novo->valor = num;
      novo->proximo = NULL;

      // é o primeiro?
      if (*lista == NULL)
         *lista = novo;
      else
      {
         aux = *lista;
         while (aux->proximo)
            aux = aux->proximo;
         aux->proximo = novo;
      }
   }
   else
      printf("Erro ao alocar memoria!\n");
}

// procedimento para inserir no meio
void inserir_no_meio(No **lista, int num, int ant)
{
   No *aux, *novo = malloc(sizeof(No));

   if (novo)
   {
      novo->valor = num;
      // é o primeiro?
      if (*lista == NULL)
      {
         novo->proximo = NULL;
         *lista = novo;
      }
      else
      {
         aux = *lista;
         while (aux->valor != ant && aux->proximo)
            aux = aux->proximo;
         novo->proximo = aux->proximo;
         aux->proximo = novo;
      }
   }
   else
      printf("Erro ao alocar memoria!\n");
}

void inserir_ordenado(No **lista, int num)
{
   No *aux, *novo = malloc(sizeof(No)); // B1 W1 M1
   novo->valor = num;                   // B1 W1 M1
   if (*lista == NULL)                  // B1 W1 M1
   {
      novo->proximo = NULL; // B1 
      *lista = novo;        // B1  
   }
   else if (novo->valor < (*lista)->valor) // M1
   {
      novo->proximo = *lista;
      *lista = novo;
   }
   else
   {
      aux = *lista;  // W1 M1
      while (aux->proximo && novo->valor > aux->proximo->valor) // W(n+1) M 1+(n+1)/2
         aux = aux->proximo; // W(n) M (n+1)/2
      novo->proximo = aux->proximo; // W1 M1
      aux->proximo = novo; // W1 M1
   }
}

void imprimir(No *no)
{
   printf("Lista: ");
   while (no)
   {
      printf("%d >> ", no->valor);
      no = no->proximo;
   }
   printf("NULL\n");
}

void buscaOrd(No *L, int x)
{
   No *aux; // B1 W1 M1
   aux = L; // B1 W1 M1
   while (aux->valor < x) // B1 W(n+1) M 1+(n+1)/2
   {
      aux = aux->proximo; // W(n) M (n+1)/2
   }
   if (aux->valor == x) // B1 W1 M1
   {
      printf("Numero %d faz parte da lista.\n", x);
   }
   else
   {
      printf("Numero %d não faz parte da lista.\n", x);
   }
   return;
}

void buscaDes(No *L, int x)
{
   No *aux; // B1 W1 M1
   aux = L; // B1 W1 M1
   int found = 0; // B1 W1 M1
   while (aux != NULL) // B1 W(n+1) M 1+(n+1)/2
   {
      if (aux->valor == x) // W(n) M(n+1)/2
      {
         printf("Numero %d encontrado.\n", x); // M1
         return;
      }
      aux = aux->proximo; // W(n) M ((n+1)/2)-1
   }
   printf("Numero %d não encontrado.\n", x); // B1 // W1
}

int main()
{
   No *lista = NULL;
   inserir_no_fim(&lista, 9);
   imprimir(lista);
   inserir_no_inicio(&lista, 1);
   imprimir(lista);
   inserir_no_meio(&lista, 5, 1);
   imprimir(lista);
   inserir_ordenado(&lista, 8);
   imprimir(lista);
   buscaOrd(lista, 5);
   buscaOrd(lista, 6);
   buscaDes(lista, 1);
   buscaDes(lista, 9);
   buscaDes(lista, 3);
   return 0;
}
