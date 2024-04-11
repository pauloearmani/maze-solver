#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "labirinto.h"

Labirinto *alocarLabirinto()
{
     Labirinto *labirinto = (Labirinto *)malloc(sizeof(Labirinto));
     if (labirinto == NULL)
     {
          printf("Erro ao alocar memória para o Labirinto.\n");
          exit(1);
     }
     labirinto->linhas = 0;
     labirinto->colunas = 0;
     labirinto->maze = NULL;
     labirinto->percurso.posicoes = NULL;
     labirinto->percurso.comprimento = 0;
     return labirinto;
}

void desalocarLabirinto(Labirinto *labirinto)
{
     if (labirinto != NULL)
     {
          if (labirinto->maze != NULL)
          {
               for (int i = 0; i < labirinto->linhas; i++)
               {
                    free(labirinto->maze[i]);
               }
               free(labirinto->maze);
          }
          if (labirinto->percurso.posicoes != NULL)
          {
               free(labirinto->percurso.posicoes);
          }
          free(labirinto);
     }
}

Labirinto *leLabirinto(int linhas, int colunas)
{
     // Aloca o Labirinto
     Labirinto *labirinto = alocarLabirinto();
     labirinto->linhas = linhas; // Atribui linhas e colunas ao labirinto
     labirinto->colunas = colunas;
     // aloca a memoria necessaria para armazenar as posicoes percorridas pelo rato
     labirinto->percurso.posicoes = (Posicao *)malloc(linhas * colunas * sizeof(Posicao));
     labirinto->maze = (Celula **)malloc(linhas * sizeof(Celula *));

     /*percorre o labirinto linha por linha, aloca a memoria necessaria para cada
    coluna e le os caracteres do labirinto
     */
     for (int i = 0; i < linhas; i++)
     {
          labirinto->maze[i] = (Celula *)malloc(colunas * sizeof(Celula));
          for (int j = 0; j < colunas; j++)
          {
               scanf("%c", &(labirinto->maze[i][j].valor));
          }
          scanf("\n");
     }

     return labirinto;
}

bool acharSaida(Posicao origem, Posicao destino, Labirinto *labirinto)
{
     // verifica se a origem e o destino sao validos e se a origem já foi visitada
     /*origem.visitado serve para evitar que caso seja encontrado um caminho
     errado o rato volte para a ultima posicao true e consiga prosseguir
     e assim achar a menor saida */
     if (!ehValido(origem, labirinto) || !ehValido(destino, labirinto) || origem.visitado)
     {
          printf("Origem: %d %d\n", origem.x, origem.y);
          return false;
     }

     // verifica se a origem eh o destino
     if (origem.x == destino.x && origem.y == destino.y) // caso base da recursão
     {
          return true;
     }
     /*marca a posicao atual(origem) como visitada tanto na estrutura labirinto
     quanto na estrutura posicao, isso evita que o rato passe varias vezes no
     mesmo lugar */
     labirinto->maze[origem.x][origem.y].visitado = true;
     origem.visitado = true;

     // Vetores que representam as direções que o rato pode ir
     int dx[] = {0, 1, 0, -1};
     int dy[] = {1, 0, -1, 0};

     /*percorre as 4 direcoes possiveis e cria uma nova posicao
     com as coordenadas atualizadas*/
     for (int i = 0; i < 4; i++)
     {
          Posicao novaPos;
          novaPos.x = origem.x + dx[i];
          novaPos.y = origem.y + dy[i];
          novaPos.visitado = false; // nova posicao inicialmente nao visitada

          /*primeiro verifica se a posicao nova eh valida e se ela nao foi visitada
          se for verdadeiro, eh chamada recursivamente com a nova posicao como
          origem, se a chamada retornar true, significa que a saida foi encontrada
          a partir da nova posicao, entao a posicao atual eh adicionada ao percurso
          */
          if (ehValido(novaPos, labirinto) && !labirinto->maze[novaPos.x][novaPos.y].visitado)
          {
               if (acharSaida(novaPos, destino, labirinto))
               {
                    labirinto->percurso.posicoes[labirinto->percurso.comprimento] = novaPos; // Adiciona a posição ao percurso
                    labirinto->percurso.comprimento++;
                    labirinto->maze[novaPos.x][novaPos.y].valor = 'o';
                    return true;
               }
          }
     }

     /*Se nenhuma das condições anteriores for atendida dentro do loop, isso
     significa que nenhuma das direções possíveis leva a saida
     */
     return false;
}

bool ehValido(Posicao pos, Labirinto *labirinto)
{
     // verifica se a posicao esta dentro do labirinto
     if (pos.x < 0 || pos.x >= labirinto->linhas || pos.y < 0 || pos.y >= labirinto->colunas)
     {
          return false;
     }

     // verifica se a posicao eh uma parede
     if (labirinto->maze[pos.x][pos.y].valor == '#' || labirinto->maze[pos.x][pos.y].valor == '*')
     {
          return false;
     }
     return true;
}

Posicao achaOrigem(Labirinto *labirinto)
{
     Posicao origem;
     origem.visitado = false;

     /* quando acha o caracter 'M' no labirinto, significa que eh a origem
     entao atribui i e j, a x e y
     */
     for (int i = 0; i < labirinto->linhas; i++)
     {
          for (int j = 0; j < labirinto->colunas; j++)
          {
               if (labirinto->maze[i][j].valor == 'M')
               {
                    origem.x = i;
                    origem.y = j;
                    return origem;
               }
          }
     }
     return origem;
}

Posicao achaDestino(Labirinto *labirinto)
{
     Posicao saida;

     /* saida.x e saida.y recebem a saida do labirinto que sera sempre fixo
     e saida.visitado recebe false para quando achar a saida, nao dar erro
     */
     saida.x = labirinto->linhas - 2;
     saida.y = labirinto->colunas - 1;
     saida.visitado = false;

     return saida;
}

void imprimePercursoNoLabirinto(Labirinto *labirinto)
{
     // imprime o percurso do rato no labirinto
     for (int i = 0; i < labirinto->linhas; i++)
     {
          for (int j = 0; j < labirinto->colunas; j++)
          {
               printf("%c", labirinto->maze[i][j].valor);
          }

          printf("\n");
     }
}

void imprimeCoordenadas(Labirinto *labirinto)
{
     // imprime as coordenadas do percurso do rato
     for (int i = labirinto->percurso.comprimento - 1; i >= 0; i--)
     {
          printf("%d, %d\n", labirinto->percurso.posicoes[i].x, labirinto->percurso.posicoes[i].y);
     }
}