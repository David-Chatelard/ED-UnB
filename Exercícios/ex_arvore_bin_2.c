/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma árvore binária parte 2
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

void rotaciona_esquerda(ab_t** p_raiz){
    if(!(*p_raiz))
        return;
    if(!(*p_raiz)->dir)
        return;

    ab_t* aux = *p_raiz;
    *p_raiz = (*p_raiz)->dir;
    aux->dir = (*p_raiz)->esq;
    (*p_raiz)->esq = aux;
}

void rotaciona_direita(ab_t** p_raiz){
    if(!(*p_raiz))
        return;
    if(!(*p_raiz)->esq)
        return;

    ab_t* aux = *p_raiz;
    *p_raiz = (*p_raiz)->esq;
    aux->esq = (*p_raiz)->dir;
    (*p_raiz)->dir = aux;
}

//Essa função funciona para a questão 1 da parte 2
void em_lista(ab_t** p_raiz){//MUDAR PARA AB_CHAR PARA ENVIAR A QUESTÃO
    if(!p_raiz)
        return;

    if(*p_raiz){
        while((*p_raiz)->dir) {
            rotaciona_esquerda(p_raiz);
        }
        em_lista(&(*p_raiz)->esq);
    }
}

//Essa função funciona para a questão 2 da parte 2
void comprime(ab_t **p_raiz, int rotacoes) {//MUDAR PARA AB_INT PARA ENVIAR A QUESTÃO
    if(!p_raiz)
        return;

    if(*p_raiz){
        if (rotacoes > 0) {
            rotaciona_direita(p_raiz);
            comprime(&(*p_raiz)->esq, rotacoes-1);
        }
    }
}

int main() {
    ab_t* raiz = NULL, *outra_raiz = NULL;
    int num_nos, i, no;

    /*raiz = cria_no('I');
    raiz->esq = cria_no('H');
    raiz->esq->dir = cria_no('J');
    raiz->dir = cria_no('G');
    raiz->dir->esq = cria_no('F');
    raiz->dir->esq->esq = cria_no('E');
    raiz->dir->esq->dir = cria_no('D');
    raiz->dir->dir = cria_no('C');
    raiz->dir->dir->esq = cria_no('B');
    raiz->dir->dir->dir = cria_no('A');*/

    raiz = cria_no(10);
    raiz->esq = cria_no(9);
    raiz->esq->esq = cria_no(8);
    raiz->esq->esq->esq = cria_no(7);
    raiz->esq->esq->esq->esq = cria_no(6);
    raiz->esq->esq->esq->esq->esq = cria_no(5);
    raiz->esq->esq->esq->esq->esq->esq = cria_no(4);
    raiz->esq->esq->esq->esq->esq->esq->esq = cria_no(3);
    raiz->esq->esq->esq->esq->esq->esq->esq->esq = cria_no(2);
    raiz->esq->esq->esq->esq->esq->esq->esq->esq->esq = cria_no(1);

    outra_raiz = cria_no(2);
    outra_raiz->esq = cria_no(1);
    outra_raiz->dir = cria_no(3);

    mostra_arvore(outra_raiz);
    printf("\n\n");

    comprime(&outra_raiz, 1);
    mostra_arvore(outra_raiz);
    printf("\n\n");



    mostra_arvore(raiz);
    printf("\n\n");

    comprime(&raiz, 0);
    mostra_arvore(raiz);
    printf("\n\n");

    comprime(&raiz, 4);
    mostra_arvore(raiz);

    /*scanf("%d", &num_nos);

    for (i = 0; i < num_nos; i++) {
        scanf("%d", &no);
        insere(&raiz, no);
    }*/

    /*mostra_arvore(raiz);
    printf("\n\n");

    em_lista(&(raiz->esq));
    mostra_arvore(raiz);
    printf("\n\n");

    em_lista(&(raiz->dir));
    mostra_arvore(raiz);
    printf("\n\n");

    em_lista(&raiz);
    mostra_arvore(raiz);*/
    libera_arvore(raiz);

    return 0;
}