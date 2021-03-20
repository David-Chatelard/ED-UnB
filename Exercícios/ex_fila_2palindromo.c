/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de uma fila e verificar se uma palavra é um 2 palíndromo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct elem {
    char letra;
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
void imprime(fila *q) {

    //usando um ponteiro auxiliar
    tipo_elem *x;
    x = q->inicio;

    //iterando na pilha
    while(x != NULL) {
        printf("%c\n", x->letra);
        x = x->lig;
    }
}

// insere x no fim de q
boolean enqueue(fila *q, char letra) {

    tipo_elem *p = malloc(sizeof(tipo_elem));
    if(p == NULL)
        return FALSE;

    p->letra = letra;
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

boolean esvazia_logicamente(fila* q){
    if(isEmpty(q))
        return FALSE;

    q->inicio = NULL;
    q->fim = NULL;

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

char* inverte(char* normal){
    int i, len;
    char* inversa;

    len = strlen(normal);
    inversa = malloc(sizeof(len+1));

    if(!inversa)
        return NULL;

    for(i = 0; i < len; i++)
        inversa[i] = normal[len - i - 1];

    inversa[len] = '\0';

    return inversa;
}

void verifica_2palindromos(char* entrada){
    fila fila_letras;
    int i, j, k, l, m = 0, len1, len2, cont = 0, cont2 = 0;
    char aux1[256], aux2[256];
    char* reverse;

    len1 = strlen(entrada);
    create(&fila_letras);

    //Percorre a entrada
    for(i = 0; i <= len1; i++){
        //Bota a palavra em aux1
        if(entrada[i] != ' ') {
            aux1[m] = entrada[i];
        }

        //Indica o fim da palavra
        if(entrada[i] == ' ')
            aux1[m] = '\0';

        if(aux1[m] != '\0') {
            m++;
            continue;
        }

        if(entrada[i] == ' ') {
            aux1[m] = '\0';
            m = 0;
        }

        len2 = strlen(aux1);
        cont = 0;
        cont2 = 0;
        //Percorre a palavra
        for(j = 0; j < len2; j++){
            if(len2 - j < 3)
                break;
            //Analisa a palavra em palavras menores
            for(k = len2-1; k >= 2; k--){
                if(j == 0 && cont2 == 0) {
                    cont2++;
                    continue;
                }
                for(l = 0; l <= k; l++)
                    aux2[l] = aux1[l+j];
                aux2[l] = '\0';
                reverse = inverte(aux2);
                if(!strcmp(reverse, aux2)) {
                    cont++;
                    break;
                }
            }
        }
        if(cont >= 2)
            printf("%s\n", aux1);
    }
}

int main() {
    char entrada[256];

    scanf("%[^\n]", entrada);

    verifica_2palindromos(entrada);

    return 0;
}