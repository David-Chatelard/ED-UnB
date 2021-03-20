/**
 * Aluno: David Fanchic Chatelard
 * Disciplina: Estrutura de Dados
 * Exercício de implementação de um grafo
*/

#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 100

/*A estrutura do grafo abaixo foi para a questão 4*/
/* Define a estrutura da informação relevante. */
typedef struct {
    int dia, mes, ano;
    char descricao[50];
} data_t;

/*A estrutura do grafo abaixo foi para a questão 4*/
/* Define a estrutura do vértice. */
typedef struct {
    char chave;
    data_t data;
} vertice_t;

/*A estrutura do grafo abaixo foi para a questão 4*/
/* typedef struct {
    vertice_t vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t; */

/*A estrutura do grafo abaixo foi para as questões 1, 2, 3 e 5*/
typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;

/* Atenção, não  modifique o trecho acima! */

/*Questão 2*/
/* Retorna o índice do vértice no vetor, caso exista, -1 caso contrário. */
int idx_vertice(grafo_t* g, char v) {
    int i;
    if(!g)
        return -1;
    for (i = 0; i < g->ordem; i++){
        if(g->vertices[i] == v)
            return i;
    }
    return -1;
}

/*Questão 3*/
/* Cria uma aresta ligando o vértice origem ao vértice destino, se existirem no grafo. */
_Bool aresta(grafo_t* grafo, char origem, char destino) {
    int indice_origem, indice_destino;

    if(!grafo)
        return false;

    indice_origem = idx_vertice(grafo, origem);
    indice_destino = idx_vertice(grafo, destino);

    if(indice_origem == -1 || indice_destino == -1)
        return false;

    grafo->arestas[indice_origem][indice_destino] = 1;
    grafo->arestas[indice_destino][indice_origem] = 1;

    return true;
}

/*Questão 4*/
/* Retorna o ponteiro para o vértice identificado pela chave, caso exista, NULL caso contrário. */
vertice_t* vertice(grafo_t* g, char chave) {
    int i;

    if(!g)
        return NULL;

    for (i = 0; i < g->ordem; i++){
        if(g->vertices[i].chave == chave)
            return &(g->vertices[i]);
    }

    return NULL;
}

/*Questão 5*/
/* Retorna a quantidade de arestas que incidem sobre um vértice. */
int grau_de_entrada(grafo_t* g, char vertice) {
    int indice, i, qtd_arestas = 0;

    if(!g)
        return 0;

    indice = idx_vertice(g, vertice);

    if(indice == -1)
        return 0;

    for (i = 0; i < TAMANHO; i++){
        if(g->arestas[i][indice] == 1)
            qtd_arestas++;
    }

    return qtd_arestas;
}

int main() {


    return 0;
}