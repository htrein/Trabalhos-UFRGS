#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#define MAX 1000

struct TNodoA
{
    char *word;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

pNodoA* InsereAVL (pNodoA *a, char* x, int *ok);
pNodoA* Caso1 (pNodoA *a, int *ok);
pNodoA* Caso2 (pNodoA *a, int *ok);
pNodoA* rotacao_direita(pNodoA* p);
pNodoA* rotacao_esquerda(pNodoA *p);
pNodoA* rotacao_dupla_direita (pNodoA* p);
pNodoA* rotacao_dupla_esquerda (pNodoA *p);
int consultaAVL(pNodoA* p, char* chave);
void palavrasComum_aux(pNodoA* avl1, pNodoA* avl2, int* countador);
int palavrasComum(pNodoA* avl1, pNodoA* avl2);
int num_nodos(pNodoA*nodo);
