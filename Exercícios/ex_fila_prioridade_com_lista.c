/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma fila de prioridade utilizando lista
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef int info_t; /* A informação a ser armazenada. */

typedef struct elemento_t {
    info_t info;
    int pos;
    struct elemento_t* prox; /* Ponteiro para o próximo elemento. */
    struct elemento_t* ant;  /* Ponteiro para o elemento anterior. */
} elemento_t;                /* Determina um elemento (nó) da lista. */

typedef elemento_t lista_t; /* A lista é uma sequência de elementos. */


elemento_t* elemento(const info_t* info, int pos, elemento_t* ant, elemento_t* prox) {
    elemento_t *e = NULL;
    e = malloc(sizeof(elemento_t));
    if (e) {
        memcpy(&(e->info), info, sizeof(info_t));
        e->pos = pos;
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

int busca_pos(const info_t *info, lista_t* lista) {
    lista_t* aux = lista;
    int i = 0;

    if(!info || !lista){
        return -1;
    }

    while(infocmp(info, &(aux->info)) && aux->prox){
        aux = aux->prox;
        i++;
    }
    if(!infocmp(info, &(aux->info))){
        return i;
    }
    return -1;
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
        e = elemento(&(*ptr_aux)->info, (*ptr_aux)->pos, (*ptr_aux)->ant, (*ptr_aux)->prox);
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

int tamanho(lista_t* lista) {
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

_Bool preenche_lista_pref(lista_t** ptr_lista_geral, lista_t** ptr_lista_pref){
    lista_t** ptr_aux = ptr_lista_geral;
    elemento_t* e = NULL;
    int i, cont = 0;

    if(!ptr_lista_geral || !(*ptr_lista_geral) || !ptr_lista_pref){
        return false;
    }

    for(i = 0;i < tamanho(*ptr_lista_geral); i++) {
        if((*ptr_aux)->info >= 60){
            e = elemento(&(*ptr_aux)->info, (*ptr_aux)->pos, NULL, NULL);
            insere(e, cont, ptr_lista_pref);
            cont++;
        }
        if((*ptr_aux)->prox){
            ptr_aux = &(*ptr_aux)->prox;
        }
    }
    return true;
}

_Bool atualiza_lista_geral(lista_t** ptr_lista_geral){
    lista_t** ptr_aux = ptr_lista_geral;
    int i, tam, pos;

    if(!ptr_lista_geral || !(*ptr_lista_geral)){
        return false;
    }

    tam = tamanho(*ptr_lista_geral);
    for(i = 0;i < tam; i++) {
        if((*ptr_aux)->info >= 60){
            pos = busca_pos(&(*ptr_aux)->info, *ptr_lista_geral);
            retira(pos, ptr_lista_geral);
        }
        else if((*ptr_aux)->prox){
            ptr_aux = &(*ptr_aux)->prox;
        }
    }
    return true;
}

void print_pref_esperado(lista_t* lista_pref){
    lista_t* aux = lista_pref;
    int i, tam;

    if(!lista_pref){
        return;
    }

    tam = tamanho(lista_pref);
    for(i = 0;i < tam;i++){
        printf("%d - %d\n", i+1, aux->pos);
        if(aux->prox){
            aux = aux->prox;
        }
    }
}

void print_geral_esperado(lista_t* lista_geral){
    lista_t* aux = lista_geral;
    int i, tam;

    if(!lista_geral){
        return;
    }

    tam = tamanho(lista_geral);
    for(i = 0;i < tam;i++){
        printf("%d - %d\n", i+1, aux->pos);
        if(aux->prox){
            aux = aux->prox;
        }
    }
}

void print_i(const info_t* info, const int pos) {
    if(info)
        printf("%d - %d\n", pos, *info);
}

void print_e(const elemento_t* e) {
    if(e) {
        print_i(&(e->info), e->pos);
    }
}

void print_l(const lista_t* lista) {
    while(lista) {
        print_e(lista);
        lista = lista->prox;
    }
}



int main() {
    lista_t* lista_geral = NULL;
    lista_t* lista_pref = NULL;
    elemento_t* e = NULL;
    int idade = 0, pos = 1;

    while(scanf("%d", &idade) > 0){
        e = elemento(&idade, pos, NULL, NULL);
        insere(e, pos-1, &lista_geral);
        pos++;
    }
    printf("Fila geral original\n");
    print_l(lista_geral);
    printf("\n");

    preenche_lista_pref(&lista_geral, &lista_pref);
    printf("Fila preferencial\n");
    print_l(lista_pref);
    printf("\n");

    atualiza_lista_geral(&lista_geral);
    printf("Fila geral atualizada\n");
    print_l(lista_geral);
    printf("\n");

    printf("Resultado esperado fila preferencial\n");
    print_pref_esperado(lista_pref);
    printf("\n");

    printf("Resultado esperado fila geral\n");
    print_geral_esperado(lista_geral);

    return 0;
}