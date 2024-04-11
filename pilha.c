#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

bool dfs(Posicao origem, Posicao destino, Labirinto *labirinto, int linhas, int colunas)
{
     // Verifica se a origem e o destino são válidos e se a origem já foi visitada
     if (!ehValido(origem, labirinto) || !ehValido(destino, labirinto) || origem.visitado)
     {
          printf("Origem: %d %d\n", origem.x, origem.y);
          return false;
     }

     // Vetores que representam as direções que o rato pode ir
     int dx[] = {0, 1, 0, -1};
     int dy[] = {1, 0, -1, 0};


     // Marca a posição atual (origem) como visitada
     labirinto->maze[origem.x][origem.y].visitado = true;

     // Empilha a origem
     Pilha *pilha = malloc(sizeof(Pilha));
     pilha->posicoes = malloc(sizeof(Posicao) * linhas * colunas);
     pilha->cabeca = 0;
     pilha->posicoes[pilha->cabeca] = origem;

     while (pilha->cabeca != -1)
     {
          Posicao atual = pilha->posicoes[pilha->cabeca--];

          // Verifica se a posição atual e o destino
          if (atual.x == destino.x && atual.y == destino.y)
          {
               return true;
          }

          // Explora todas as direções possíveis
          for (int i = 0; i < 4; i++)
          {
               Posicao novaPos;
               novaPos.x = atual.x + dx[i];
               novaPos.y = atual.y + dy[i];
               novaPos.visitado = false; // Nova posição inicialmente não visitada

               // Verifica se a nova posição é válida e se não foi visitada
               if (ehValido(novaPos, labirinto) && !labirinto->maze[novaPos.x][novaPos.y].visitado)
               {
                    // Marca a nova posição como visitada
                    labirinto->maze[novaPos.x][novaPos.y].visitado = true;
                    labirinto->percurso.posicoes[labirinto->percurso.comprimento] = novaPos; // Adiciona a posição ao percurso
                    labirinto->percurso.comprimento++;
                    labirinto->maze[novaPos.x][novaPos.y].valor = 'o';

                    // Empilha a nova posição
                    pilha->posicoes[++pilha->cabeca] = novaPos;
               }
          }
     }

     // Se a cabeca ficar vazia e o destino não for alcançado, não há saída
     return false;
}