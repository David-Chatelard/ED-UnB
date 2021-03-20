/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Implementação de uma lista encadeada
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


typedef int info_t;

typedef struct elemento_t {
    info_t info;
    struct elemento_t * prox;
} elemento_t;

typedef elemento_t lista_t;


//Assinaturas
elemento_t* elemento(const info_t* info, elemento_t* prox);
void libera(elemento_t** ptr);
_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista);
elemento_t* retira(unsigned int pos, lista_t** ptr_lista);






//Implementação
_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista){
    lista_t** ptr_aux = ptr_lista;
    int i;

    if(!e || !ptr_lista)
        return false;

    for(i = 0; i < pos && *ptr_aux; i++){
        ptr_aux =  &(*ptr_aux)->prox;
    }

    if(i == pos){
        e->prox = *ptr_aux;
        *ptr_aux = e;
        return true;
    }

    return false;
}


elemento_t* retira(unsigned int pos, lista_t** ptr_lista){
    lista_t** ptr_aux = ptr_lista;
    int i;

    if(!ptr_lista || !(*ptr_lista))
        return NULL;

    for(i = 0; i < pos && *ptr_aux; i++){
        ptr_aux =  &(*ptr_aux)->prox;
    }

    if(i == pos){
        elemento_t* aux = *ptr_aux;
        *ptr_aux = (*ptr_aux)->prox;
        return aux;
    }

    return NULL;
}





elemento_t* elemento(const info_t* info, elemento_t* prox){
    elemento_t* e = (elemento_t *) malloc(sizeof(elemento_t));

    if(e){
        memcpy(&(e->info), info, sizeof(info_t));
        e->prox = prox;
    }
    return e;
}

void libera(elemento_t** ptr){
    if( ptr && (*ptr)){
        free(*ptr);
        *ptr = NULL;
    }
}

void testa_insere() {
    assert(!insere(NULL, 0, NULL));

    lista_t* lista = NULL;
    assert(!insere(NULL, 0, &lista));

    int info = 3;
    elemento_t* e3 = elemento(&info, NULL);
    assert(!insere(e3, -1, &lista));
    assert(!insere(e3, 7, &lista));
    assert(insere(e3, 0, &lista));
    assert(lista);
    //assert(0 == elementocmp(lista, e3));

    info = 1;
    elemento_t* e1 = elemento(&info, NULL);
    assert(insere(e1, 0, &lista));
    //assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e3);

    info = 2;
    elemento_t* e2 = elemento(&info, NULL);
    assert(insere(e2, 1, &lista));
    //assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->prox == e3);

    info = 4;
    elemento_t* e4 = elemento(&info, NULL);
    assert(insere(e4, 3, &lista));
    //assert(0 == elementocmp(lista, e1));
    assert(lista->prox == e2);
    assert(e2->prox == e3);
    assert(e3->prox == e4);
    assert(e4->prox == NULL);



    //esvazia(&lista);
}


void testa_retira() {
    lista_t* lista = NULL;

    assert(!retira(0, &lista));

    int info = 3;
    insere(elemento(&info, NULL), 0, &lista);
    info = 2;
    insere(elemento(&info, NULL), 0, &lista);
    info = 1;
    insere(elemento(&info, NULL), 0, &lista);

    elemento_t* e = retira(1, &lista);
    assert(e);
    assert(2 == e->info);
//    assert(2 == tamanho(lista));
    assert(1 == lista->info);
    assert(3 == lista->prox->info);
    libera(&e);

    e = retira(1, &lista);
    assert(e);
    assert(3 == e->info);
//    assert(1 == tamanho(lista));
    assert(1 == lista->info);
    libera(&e);

    e = retira(0, &lista);
    assert(e);
    assert(1 == e->info);
//    assert(vazia(lista));

    printf("Teste\n");
}


int main() {
    testa_insere();
    testa_retira();

}