#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "labirinto.h"
#include "fila.h"
#include "pilha.h"

int main()
{
     int linhas, colunas;
     char tipo;
     scanf("%d %d ", &linhas, &colunas);
     scanf("%c ", &tipo);

     Labirinto *labirinto = leLabirinto(linhas, colunas);

     labirinto->origem = achaOrigem(labirinto);
     labirinto->saida = achaDestino(labirinto);

     switch (tipo)
     {
     case 'r':
          acharSaida(labirinto->origem, labirinto->saida, labirinto);
          break;
     case 'f':
          bfs(labirinto->origem, labirinto->saida, labirinto, linhas, colunas);
          break;
     case 'p':
          dfs(labirinto->origem, labirinto->saida, labirinto, linhas, colunas);
          break;
     }

     printf("%d \n", labirinto->percurso.comprimento); // imprime nro de passos do percurso
     imprimePercursoNoLabirinto(labirinto);

     desalocarLabirinto(labirinto);

     return 0;
}