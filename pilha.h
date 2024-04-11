#ifndef PILHA_H
#define PILHA_H
#include "labirinto.h"

typedef struct {
     Posicao *posicoes;
     int cabeca;
} Pilha;

bool dfs(Posicao origem, Posicao destino, Labirinto *labirinto, int linhas, int colunas);

#endif // PILHA_H