/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma árvore binária parte 3
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

//Essa função foi modificada para essa questão 3
void em_lista(ab_t** p_raiz){//MUDAR PARA AB_CHAR PARA ENVIAR A QUESTÃO
    if(!p_raiz)
        return;

    if(*p_raiz){
        while((*p_raiz)->esq) {
            rotaciona_direita(p_raiz);
        }
        em_lista(&(*p_raiz)->dir);
    }
}

//Essa função foi modificada para essa questão 3
void comprime(ab_t **p_raiz, int rotacoes) {//MUDAR PARA AB_INT PARA ENVIAR A QUESTÃO
    if(!p_raiz)
        return;

    if(*p_raiz){
        if (rotacoes > 0) {
            rotaciona_esquerda(p_raiz);
            comprime(&(*p_raiz)->dir, rotacoes-1);
        }
    }
}

int altura(ab_t* raiz){//MUDAR PARA AB_INT PARA ENVIAR A QUESTÃO
    int alt_esq = 0, alt_dir = 0;

    if(!raiz)
        return 0;

    alt_esq = altura(raiz->esq);
    alt_dir = altura(raiz->dir);

    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

//Essa função funciona para a questão 3 da parte 2
void dsw(ab_t **p_raiz) {//MUDAR PARA AB_INT PARA ENVIAR A QUESTÃO
    int rotacoes;
    if(!p_raiz)
        return;

    if(*p_raiz){
        em_lista(p_raiz);
        rotacoes = (altura(*p_raiz) - 1) / 2;
        comprime(p_raiz, rotacoes);
        while(rotacoes > 1){
            rotacoes /= 2;
            comprime(p_raiz, rotacoes);
        }
    }
}

int main() {
    ab_t* a2 = NULL, *a1 = NULL, *a3 = NULL, *a4 = NULL, *sexta_arvore = NULL;

    /*raiz = cria_no(10);
    raiz->dir = cria_no(9);
    raiz->dir->dir = cria_no(8);
    raiz->dir->dir->dir = cria_no(7);
    raiz->dir->dir->dir->dir = cria_no(6);
    raiz->dir->dir->dir->dir->dir = cria_no(5);
    raiz->dir->dir->dir->dir->dir->dir = cria_no(4);
    raiz->dir->dir->dir->dir->dir->dir->dir = cria_no(3);
    raiz->dir->dir->dir->dir->dir->dir->dir->dir = cria_no(2);
    raiz->dir->dir->dir->dir->dir->dir->dir->dir->dir = cria_no(1);*/

    a2 = cria_no(10);
    a2->esq = cria_no(9);
    a2->esq->esq = cria_no(8);
    a2->esq->esq->esq = cria_no(7);
    a2->esq->esq->esq->esq = cria_no(6);
    a2->esq->esq->esq->esq->esq = cria_no(5);
    a2->esq->esq->esq->esq->esq->esq = cria_no(4);
    a2->esq->esq->esq->esq->esq->esq->esq = cria_no(3);
    a2->esq->esq->esq->esq->esq->esq->esq->esq = cria_no(2);
    a2->esq->esq->esq->esq->esq->esq->esq->esq->esq = cria_no(1);

    a1 = cria_no(1);
    a1->dir = cria_no(2);
    a1->dir->dir = cria_no(3);

    a3 = cria_no(1);
    a3->dir = cria_no(2);
    a3->dir->dir = cria_no(3);
    a3->dir->dir->dir = cria_no(4);
    a3->dir->dir->dir->dir = cria_no(5);
    a3->dir->dir->dir->dir->dir = cria_no(6);
    a3->dir->dir->dir->dir->dir->dir = cria_no(7);
    a3->dir->dir->dir->dir->dir->dir->dir = cria_no(8);
    a3->dir->dir->dir->dir->dir->dir->dir->dir = cria_no(9);
    a3->dir->dir->dir->dir->dir->dir->dir->dir->dir = cria_no(10);

    a4 = cria_no(4);
    a4->esq = cria_no(2);
    a4->esq->esq = cria_no(1);
    a4->esq->dir = cria_no(3);
    a4->dir = cria_no(8);
    a4->dir->esq = cria_no(6);
    a4->dir->esq->esq = cria_no(5);
    a4->dir->esq->dir = cria_no(7);
    a4->dir->dir = cria_no(9);
    a4->dir->dir->dir = cria_no(10);

    sexta_arvore =cria_no(12);
    sexta_arvore->esq =cria_no(10);
    sexta_arvore->esq->dir = cria_no(11);
    sexta_arvore->esq->esq =cria_no(8);
    sexta_arvore->esq->esq->dir = cria_no(9);
    sexta_arvore->esq->esq->esq = cria_no(6);
    sexta_arvore->esq->esq->esq->dir = cria_no(7);
    sexta_arvore->esq->esq->esq->esq = cria_no(4);
    sexta_arvore->esq->esq->esq->esq->dir = cria_no(5);
    sexta_arvore->esq->esq->esq->esq->esq = cria_no(2);
    sexta_arvore->esq->esq->esq->esq->esq->dir = cria_no(3);
    sexta_arvore->esq->esq->esq->esq->esq->esq = cria_no(1);
    sexta_arvore->dir = cria_no(13);


    mostra_arvore(a1);
    printf("\n\n");
    dsw(&a1);
    mostra_arvore(a1);
    printf("\n\n");

    dsw(&a1);
    mostra_arvore(a1);
    printf("\n\n");



    mostra_arvore(a2);
    printf("\n\n");
    dsw(&a2);
    mostra_arvore(a2);
    printf("\n\n");



    mostra_arvore(a3);
    printf("\n\n");
    dsw(&a3);
    mostra_arvore(a3);
    printf("\n\n");



    mostra_arvore(a4);
    printf("\n\n");
    dsw(&a4);
    mostra_arvore(a4);
    printf("\n\n");

    mostra_arvore(sexta_arvore);
    printf("\n\n");
    dsw(&sexta_arvore);
    mostra_arvore(sexta_arvore);
    printf("\n\n");

    /*mostra_arvore(outra_raiz);
    printf("\n\n");

    comprime(&outra_raiz, 1);
    mostra_arvore(outra_raiz);
    printf("\n\n");


    mostra_arvore(raiz);
    printf("\n\n");

    em_lista(&raiz);
    mostra_arvore(raiz);
    printf("\n\n");

    comprime(&raiz, 4);
    mostra_arvore(raiz);*/

    libera_arvore(a1);
    libera_arvore(a2);
    libera_arvore(a3);
    libera_arvore(a4);
    libera_arvore(sexta_arvore);


    return 0;
}