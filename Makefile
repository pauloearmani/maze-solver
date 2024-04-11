all: labirinto.o fila.o pilha.o main.o
	@gcc labirinto.o fila.o pilha.o main.o -o exe
	@rm *.o
labirinto.o: labirinto.c
	@gcc labirinto.c -c
fila.o: fila.c
	@gcc fila.c -c
pilha.o: pilha.c
	@gcc pilha.c -c
main.o: main.c
	@gcc main.c -c
run:
	@./exe