/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma árvore binária parte 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int dado_t;

typedef struct ab_t{
    dado_t dado;
    struct ab_t* esq;
    struct ab_t* dir;
} ab_t;

ab_t* cria_no(dado_t dado){
    ab_t* no = malloc(sizeof(ab_t));

    if(!no)
        return NULL;

    no->esq = NULL;
    no->dir = NULL;
    memcpy(&no->dado, &dado, sizeof(dado_t));

    return no;
}

/*Se for menor ou igual insere na esquerda, se for maior insere na direita funciona com int*/
int insere(ab_t** p_raiz, dado_t dado){
    if(!(*p_raiz)){
        *p_raiz = cria_no(dado);
        return 1;
    }

    if((*p_raiz)->dado >= dado)
        insere(&(*p_raiz)->esq, dado);
    else
        insere(&(*p_raiz)->dir, dado);

    return 1;

}

void mostra_arvore(ab_t* raiz) {
    if(!raiz){
        printf("()");
        return;
    }
    printf("(%d", raiz->dado);
    printf(" ");
    mostra_arvore(raiz->esq);
    printf(" ");
    mostra_arvore(raiz->dir);
    printf(")");
}

void libera_arvore(ab_t* raiz){
    if(!raiz)
        return;

    libera_arvore(raiz->esq);
    libera_arvore(raiz->dir);

    free(raiz);
    raiz = NULL;
}

int main() {
    ab_t* raiz = NULL;
    int num_nos, i, no;

    scanf("%d", &num_nos);

    for (i = 0; i < num_nos; i++) {
        scanf("%d", &no);
        insere(&raiz, no);
    }

    mostra_arvore(raiz);
    libera_arvore(raiz);

    return 0;
}