#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fila.h"

bool bfs(Posicao origem, Posicao destino, Labirinto *labirinto, int linhas, int colunas)
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

     // Inicialização da fila para o BFS
     Fila *fila = malloc(sizeof(Fila));
     fila->posicoes = malloc(sizeof(Posicao) * linhas * colunas);
     fila->inicio = 0;
     fila->fim = 0;

     // Marca a posição atual (origem) como visitada
     labirinto->maze[origem.x][origem.y].visitado = true;

     // Adiciona a origem à fila
     fila->posicoes[fila->fim] = origem;
     fila->fim++;

     while (fila->inicio != fila->fim)
     {
          Posicao atual = fila->posicoes[fila->inicio];
          fila->inicio++;

          // Verifica se a posição atual é o destino
          if (atual.x == destino.x && atual.y == destino.y - 1)
          {
               labirinto->maze[destino.x][destino.y].visitado = true;
               labirinto->percurso.posicoes[labirinto->percurso.comprimento] = destino; // Adiciona a posição ao percurso
               labirinto->maze[destino.x][destino.y].valor = 'o';
               labirinto->percurso.comprimento++;

               free(fila->posicoes);
               free(fila);
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
                    labirinto->maze[novaPos.x][novaPos.y].valor = 'o';
                    labirinto->percurso.comprimento++;
                    // Enfileira a nova posição
                    fila->posicoes[fila->fim] = novaPos;
                    fila->fim++;
               }
          }
     }
     // Se a fila ficar vazia e o destino não for alcançado, não há saída
     free(fila->posicoes);
     free(fila);
     return false;
}