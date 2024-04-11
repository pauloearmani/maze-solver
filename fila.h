#ifndef FILA_H
#define FILA_H
#include "labirinto.h"

typedef struct {
    Posicao *posicoes;
    int inicio;
    int fim;
} Fila;

bool bfs(Posicao origem, Posicao destino, Labirinto* labirinto, int linhas, int colunas);

#endif // FILA_H