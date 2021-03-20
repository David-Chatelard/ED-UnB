/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Implementação de uma pilha dinâmica
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int info_t;

typedef struct elemento{
    info_t info;
    struct elemento* lig;
} elemento_t;

typedef struct{
    elemento_t* topo;
} pilha_t;

void cria_pilha(pilha_t* pilha){
    pilha->topo = NULL;
}

elemento_t* cria_elemento(info_t* info, elemento_t* lig){
    elemento_t* aux = malloc(sizeof(elemento_t));

    if(!aux)
        return NULL;

    memcpy(&(aux->info), info, sizeof(info_t));
    aux->lig = lig;

    return aux;
}

int vazia(pilha_t* pilha){
    return (pilha->topo == NULL);
}

int empilha(elemento_t* e, pilha_t* pilha){
    if(!e)
        return 0;
    e->lig = pilha->topo;
    pilha->topo = e;

    return 1;
}

elemento_t* desempilha(pilha_t* pilha){
    elemento_t* aux = NULL;

    if(vazia(pilha))
        return NULL;

    aux = pilha->topo;
    pilha->topo = pilha->topo->lig;

    return aux;
}

int tamanho(pilha_t* pilha){
    elemento_t* aux = pilha->topo;
    int cont = 0;

    if(vazia(pilha))
        return 0;

    while(aux){
        cont++;
        aux = aux->lig;
    }
    return cont;
}

void libera_pilha(pilha_t* pilha) {
    elemento_t *aux = NULL;

    if (vazia(pilha))
        return;
    while (!vazia(pilha)) { //testar se a condição do while funciona!!!!
        aux = desempilha(pilha);
        free(aux);
    }
}

void print_i(info_t* info){
    if(info)
        printf("%d\n", *info);
}

void print_e(elemento_t* e){
    if(e)
        print_i(&(e->info));
}

void print_p(pilha_t* pilha){
    elemento_t* aux = pilha->topo;
    while(aux){
        print_e(aux);
        aux = aux->lig;
    }
}

int main() {
    pilha_t pilha;
    elemento_t* e = NULL;
    int i;

    cria_pilha(&pilha);

    for(i = 0;i < 5;i++) {
        e = cria_elemento(&i, NULL);
        empilha(e, &pilha);
    }
    print_p(&pilha);

    return 0;
}