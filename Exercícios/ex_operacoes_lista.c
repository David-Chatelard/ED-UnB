/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de operações de uma lista
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
} elemento_t;

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

void libera(elemento_t** ptr) {
    if(ptr && (*ptr)){
        free(*ptr);
        *ptr = NULL;
    }

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

_Bool vazia(const lista_t *lista) {
    if(lista){
        return false;
    }
    return true;
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
        printf("%d\n", *info);
}

void print_e(const elemento_t* e) {
    if(e) {
        print_i(&(e->info));
    }
}

void print_l(const lista_t* lista) {
    int i = 0;
    printf("\n");
    while(lista) {
        print_e(lista);
        lista = lista->prox;
        ++i;
    }
}


int main() {
    lista_t* lista = NULL;
    elemento_t* e = NULL;
    char comando;
    info_t dado;

    do{
        scanf("%c", &comando);
        if(comando == 'X'){
            print_l(lista);
            break;
        }
        if(comando == 'P'){
            e = retira(tamanho(lista)-1, &lista);
            print_e(e);
        }
        else if(comando == 'D'){
            e = retira(0, &lista);
            print_e(e);
        }
        if(comando == 'I' || comando == 'F') {
            scanf("%d", &dado);
            getchar();
            e = elemento(&dado, NULL, NULL);
        }
        if(comando == 'I'){
            insere(e, 0, &lista);
        }
        else if(comando == 'F'){
            insere(e, tamanho(lista), &lista);
        }

    } while(1);
    //esvazia(&lista);

    return 0;
}