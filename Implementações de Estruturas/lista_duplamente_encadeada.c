/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Implementação de uma lista duplamente encadeada
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int info_t; /* A informação a ser armazenada. */

typedef struct elemento_t {
    info_t info;
    struct elemento_t* prox; /* Ponteiro para o próximo elemento. */
    struct elemento_t* ant;  /* Ponteiro para o elemento anterior. */
} elemento_t;                /* Determina um elemento (nó) da lista. */

typedef elemento_t lista_t; /* A lista é uma sequência de elementos. */

elemento_t* elemento(const info_t* info, elemento_t* ant, elemento_t* prox) {
    elemento_t *e = NULL;
    e = malloc(sizeof(elemento_t));
    if (e) {
        memcpy(&(e->info), info, sizeof(info_t));
        e->prox = prox;
        e->ant = ant;
    }
    return e;
}

_Bool vazia(const lista_t *lista) {
    if(lista){
        return false;
    }
    return true;
}

void libera(elemento_t** ptr) {
    if(ptr && (*ptr)){
        free(*ptr);
        *ptr = NULL;
    }

}

int infocmp(const info_t* e1, const info_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return (*e1) - (*e2);
}

int elementocmp(const elemento_t* e1, const elemento_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return infocmp(&(e1->info), &(e2->info));
}

_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista) {
    lista_t** ptr_aux = ptr_lista;

    int i;

    if(!e || !ptr_lista){
        return false;
    }
    for(i = 0;i < pos && *ptr_aux; i++){
        ptr_aux = &(*ptr_aux)->prox;
    }
    if(i == pos){
        e->prox = *ptr_aux;
        if((*ptr_lista) != NULL && (*ptr_aux) != NULL) { /*Verifica se a lista não é vazia e se não é a última posição*/
            e->ant = (*ptr_aux)->ant;
            (*ptr_aux)->ant = e;
        }
        else if((*ptr_lista) != NULL && (*ptr_aux) == NULL){/*Verifica se a lista não é vazia e se é a última posição*/
            ptr_aux = ptr_lista;
            for(i = 0;i < (pos-1) && *ptr_aux; i++){
                ptr_aux = &(*ptr_aux)->prox;
            }
            e->ant = *ptr_aux;
            (*ptr_aux)->prox = e;
            return true;
        }
        *ptr_aux = e;
        return true;
    }
    return false;
}

_Bool insere_em_ordem(elemento_t* e, lista_t** ptr_lista){
    lista_t** ptr_aux = ptr_lista;
    int i = 0;

    if(!e || !ptr_lista){
        return false;
    }

    while(elementocmp(e, *ptr_aux) > 0 && (*ptr_aux)){
        ptr_aux = &(*ptr_aux)->prox;
        i++;
    }
    return insere(e, i, ptr_lista);
}

elemento_t* retira(unsigned int pos, lista_t** ptr_lista) {
    lista_t** ptr_aux = ptr_lista;
    elemento_t* e;
    int i;

    if(!ptr_lista || !(*ptr_lista)){
        return NULL;
    }

    for(i = 0;i < pos && (*ptr_aux)->prox;i++){
        ptr_aux = &(*ptr_aux)->prox;
    }
    if(i == pos){
        e = elemento(&(*ptr_aux)->info, (*ptr_aux)->ant, (*ptr_aux)->prox);
        if((*ptr_aux)->prox != NULL) {
            (*ptr_aux)->prox->ant = (*ptr_aux)->ant;
        }
        *ptr_aux = (*ptr_aux)->prox;
        return e;
    }
    return NULL;
}

elemento_t* retira_em_ordem(info_t* info, lista_t** ptr_lista) {
    lista_t** ptr_aux = ptr_lista;
    int i = 0;

    if(!info || !ptr_lista){
        return NULL;
    }

    while(infocmp(info, &(*ptr_aux)->info) && (*ptr_aux)){
        ptr_aux = &(*ptr_aux)->prox;
        i++;
    }
    if(!infocmp(info, &(*ptr_aux)->info)){
        return retira(i, ptr_lista);
    }
    return NULL;
}

void esvazia(lista_t** ptr_lista) {
    elemento_t* e = NULL;

    if(!ptr_lista){
        return;
    }
    if(vazia(*ptr_lista)){
        return;
    }

    while(!vazia(*ptr_lista)){
        e = retira(0, ptr_lista);
        libera(&e);
    }

}

elemento_t* busca(const info_t *info, lista_t* lista) {
    lista_t* aux = lista;

    if(!info || !lista){
        return NULL;
    }

    while(infocmp(info, &(aux->info)) && aux->prox){
        aux = aux->prox;
    }
    if(!infocmp(info, &(aux->info))){
        return aux;
    }
    return NULL;
}

unsigned int tamanho(lista_t* lista) {
    lista_t* aux = lista;
    int cont = 1; /*Começa em 1, pois caso a lista só tenha 1 elemento não vai entrar no while*/

    if(!lista){ /*Caso a lista esteja vazia*/
        return 0;
    }

    while(aux->prox){
        aux = aux->prox;
        cont++;
    }
    return cont;
}

void print_i(const info_t* info) {
    if(info)
        printf("%d", *info);
}

void print_e(const elemento_t* e) {
    if(e) {
        print_i(&(e->info));

        printf(" - ");

        if(e->ant)
            printf("1");
        else
            printf("0");

        printf(" - ");

        if(e->prox)
            printf("1\n");
        else
            printf("0\n");
    }
}

void print_l(const lista_t* lista) {
    while(lista) {
        print_e(lista);
        lista = lista->prox;
    }
}

void print_inv(lista_t* lista){
    lista_t* aux = NULL;
    lista_t* last = lista;

    if(!lista)
        return;

    while(last){
        if(last->prox)
            last = last->prox;
        else
            break;
    }
    aux = last;
    while(aux){
        print_e(aux);
        aux = aux->ant;
    }
}

int main() {
    lista_t* lista = NULL;
    elemento_t* e = NULL;
    int dado = 0, pos = 0;

    while(scanf("%d", &dado) > 0){
        e = elemento(&dado, NULL, NULL);
        insere(e, pos, &lista);
        pos++;
    }

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    dado = 43;
    e = elemento(&dado, NULL, NULL);
    insere(e, tamanho(lista), &lista);

    dado = 65;
    e = elemento(&dado, NULL, NULL);
    insere(e, tamanho(lista), &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    dado = 56;
    e = elemento(&dado, NULL, NULL);
    insere(e, 0, &lista);

    dado = 12;
    e = elemento(&dado, NULL, NULL);
    insere(e, 0, &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    dado = 10;
    e = elemento(&dado, NULL, NULL);
    insere(e, 2, &lista);

    dado = 15;
    e = elemento(&dado, NULL, NULL);
    insere(e, 0, &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    retira(tamanho(lista)-1, &lista);
    retira(tamanho(lista)-1, &lista);
    retira(tamanho(lista)-1, &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    retira(0, &lista);
    retira(0, &lista);
    retira(0, &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    retira(tamanho(lista)-1, &lista);
    retira(2, &lista);

    print_l(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    print_inv(lista);
    printf("Tamanho: %d\n", tamanho(lista));
    printf("\n");

    esvazia(&lista);

    return 0;
}