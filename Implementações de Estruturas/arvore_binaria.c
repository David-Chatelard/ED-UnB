/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Implementação de uma árvore binária
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

int altura(ab_t* raiz){
    int alt_esq = 0, alt_dir = 0;

    if(!raiz)
        return 0;

    alt_esq = altura(raiz->esq);
    alt_dir = altura(raiz->dir);

    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

/*Se for menor insere na esquerda, se for maior insere na direita funciona com int*/
ab_t* insere(ab_t* raiz, dado_t dado){
    if(!raiz)
        return cria_no(dado);

    if(raiz->dado > dado)
        raiz->esq = insere(raiz->esq, dado);
    else
        raiz->dir = insere(raiz->dir, dado);

    return raiz;

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


int main() {
    ab_t* raiz = cria_no(1);
    raiz->esq = cria_no(2);
    raiz->dir = cria_no(3);
    raiz->dir->dir = cria_no(4);
    mostra_arvore(raiz);

    return 0;
}