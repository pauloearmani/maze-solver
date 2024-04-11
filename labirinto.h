#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct {
    int x;
    int y;
    bool visitado;
} Posicao;

typedef struct {
    Posicao *posicoes;
    int comprimento;
} Percurso; 

typedef struct {
    char valor;
    bool visitado;
} Celula;

typedef struct {
    int linhas;
    int colunas;
    Celula** maze;
    Posicao origem;
    Posicao saida;
    Percurso percurso;
} Labirinto;

Labirinto* alocarLabirinto();
void desalocarLabirinto(Labirinto* labirinto);
Labirinto* leLabirinto();
bool acharSaida(Posicao origem, Posicao destino, Labirinto *labirinto);
bool ehValido(Posicao pos, Labirinto* labirinto);
Posicao achaOrigem(Labirinto* labirinto);
Posicao achaDestino(Labirinto* labirinto);
void imprimePercursoNoLabirinto(Labirinto* labirinto);
void imprimeCoordenadas(Labirinto* labirinto);
bool dfs(Posicao origem, Posicao destino, Labirinto* labirinto, int linhas, int colunas);



#endif // LABIRINTO_H