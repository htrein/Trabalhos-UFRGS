#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"

int num_nodos(pNodoA*nodo)
{
    if(nodo != NULL)
        return 1 + num_nodos(nodo->esq) + num_nodos(nodo->dir);
    else
        return 0;
}

int consultaAVL(pNodoA* p, char* chave)
{
    if(p == NULL)
        return 0;
    while(p != NULL)
    {
        if(strcmp(p->word, chave)== 0)
        {
            return 1;
        }
        else if(strcmp(p->word, chave) > 0)
        {
            p = p->esq;
        }
        else
            p = p->dir;
    }
    return 0;
}


pNodoA* InsereAVL (pNodoA *a, char* x, int *ok)
{

    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->word = (char*)malloc(strlen(x)+1);
        strcpy(a->word, x);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp(x, a->word) < 0)
    {
        a->esq = InsereAVL(a->esq,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a=Caso1(a,ok);
                break;
            }
        }
    }
    else if(strcmp(x, a->word) > 0)
    {
        a->dir = InsereAVL(a->dir,x,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }

    return a;
}

pNodoA* Caso1 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a, int *ok)
{
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

pNodoA* rotacao_esquerda(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

pNodoA* rotacao_dupla_direita (pNodoA* p)
{
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
    else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;
    p = v;
    return p;
}


pNodoA* rotacao_dupla_esquerda (pNodoA *p)
{
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
    else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    p = y;
    return p;
}

int palavrasComum(pNodoA* avl1, pNodoA* avl2)
{
    int contador = 0;

    if (avl1 == NULL || avl2 == NULL) //se uma ou as duas árvores estiverem vazias, quer dizer que não há palavras em comum
    {
        return 0;
    }

    palavrasComum_aux(avl1, avl2, &contador); //chama auxiliar

    return contador; //número de palavras em comum
}

void palavrasComum_aux(pNodoA* avl1, pNodoA* avl2, int* contador)//vai percorrer a avl1 nodo a nodo e comparar com a avl2
{
    if (avl1 == NULL)//retorna quando a avl1 já for completamente percorrida
    {
        return;
    }

    if (consultaAVL(avl2, avl1->word) == 1)//se a palavra da avl1 estiver presente em avl2 aumenta o contador
    {
        *contador = *contador + 1;
    }

    //chama recursivamente para percorrer toda avl1
    palavrasComum_aux(avl1->esq, avl2, contador);
    palavrasComum_aux(avl1->dir, avl2, contador);
}

