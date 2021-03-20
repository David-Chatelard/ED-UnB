/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma fila de prioridade
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define boolean int
#define TRUE 1
#define FALSE 0
#define TAM 10

typedef struct elem {
    char nome[51];
    struct elem *lig;
} tipo_elem;

typedef struct{
    tipo_elem *inicio;
    tipo_elem *fim;
} fila;

// cria fila vazia com dois ponteiros
void create(fila *q) {
    q->inicio = NULL;
    q->fim = NULL;
}

// testa se q está vazia
boolean isEmpty (fila *q) {
    return (q->inicio == NULL);
}

// imprime q
void imprime(fila *q, int prioridade) {

    //usando um ponteiro auxiliar
    tipo_elem *x;
    x = q->inicio;

    //iterando na pilha
    while(x != NULL) {
        printf("Atividade: %s Prioridade: #%d\n", x->nome, prioridade);
        x = x->lig;
    }
}

// insere x no fim de q
boolean enqueue(fila *q, char* nome) {

    tipo_elem *p = malloc(sizeof(tipo_elem));
    if(p == NULL)
        return FALSE;

    strcpy(p->nome, nome);
    p->lig = NULL;

    if(isEmpty(q)) {
        q->inicio = p;
    } else {
        q->fim->lig = p;
    }

    q->fim = p;
    return TRUE;
}

// remove do inicio de q
boolean dequeue(fila *q) {

    tipo_elem *p;
    if (isEmpty(q)) {
        return FALSE;
    }

    p = q->inicio;
    q->inicio = p->lig;

    if(q->inicio == NULL) {
        q->fim = NULL;
    }

    free(p);
    return TRUE;
}

int tamanho_fila(fila* q){
    int cont = 0;
    //usando um ponteiro auxiliar
    tipo_elem *x;
    x = q->inicio;

    //iterando na pilha
    while(x != NULL) {
        cont++;
        x = x->lig;
    }
    return cont;
}

int main() {
    fila fila_prioridade[TAM];
    char atividade[51];
    int prioridade = 0, i, retiradas = 0, cont = 0, aux_ret;

    for(i = 0;i < TAM;i++){
        create(&(fila_prioridade[i]));
    }

    do{
        scanf("%s", atividade);
        if(('A' <= atividade[0] && atividade[0] <= 'Z') || ('a' <= atividade[0] && atividade[0] <= 'z')){
            scanf("%d", &prioridade);
            enqueue(&(fila_prioridade[prioridade-1]), atividade);
            cont++;
        }
        else{
            retiradas = atoi(atividade);
            aux_ret = retiradas;
            break;
        }
    }while(1);

    if(retiradas != 0){
        for(i = 0;i < TAM;i++){
            if(isEmpty(&(fila_prioridade[i])))
                continue;
            /*if(tamanho_fila(&(fila_prioridade[i])) > retiradas){
                while(!isEmpty(&(fila_prioridade[i])))
                    dequeue(&(fila_prioridade[i]));
            }*/
            while(retiradas != 0){
                if(isEmpty(&(fila_prioridade[i])))
                    break;
                dequeue(&(fila_prioridade[i]));
                retiradas--;
            }
        }
    }

    if((cont-aux_ret) < 0) {
        printf("Tamanho da fila: 0\n");
    }

    else {
        printf("Tamanho da fila: %d\n", cont - aux_ret);
        for (i = 0; i < TAM; i++) {
            imprime(&(fila_prioridade[i]), i + 1);
        }
    }

    return 0;
}