/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Implementação das operações de uma pilha estática
*/

#include "pilha.h"

#define TRUE 1
#define FALSE 0
#define boolean int
#define TamPilha 100

/* cria uma pilha vazia P */
void Create(Pilha *P) {
    P->topo=-1;
    return;
}

/* esvazia logicamente a pilha P */
void Empty(Pilha *P) {
    P->topo=-1;
    return;
}

/* retorna true se a pilha estiver vazia; false caso contrário */
boolean IsEmpty(Pilha *P) {
    return (P->topo==-1);
}

/* verifica se P cresceu até o final do array */
boolean IsFull(Pilha *P) {
    return (P->topo==TamPilha-1);
}

/* empilha o valor da variável X na pilha P */
boolean Push(Pilha *P, elem *X) {
    if (!IsFull(P)) {
        P->topo++;
        P->A[P->topo]=*X;
        return TRUE;
    }
    return FALSE;
}

/*desempilha P e retorna em X o valor do elemento que estava no topo de P; 
retorna TRUE se sucesso; FALSE, c.c. */
boolean Pop(Pilha *P, elem *X) {
    if (!IsEmpty(P)) {
        *X=P->A[P->topo];
        P->topo--;
        return TRUE;
    }
    return FALSE;
}

/* retorna o valor do elemento do topo de P, sem desempilhar – chamada apenas 
se Pilha P não estiver vazia!!! */
elem Top(Pilha *P) {
    return P->A[P->topo];
}
