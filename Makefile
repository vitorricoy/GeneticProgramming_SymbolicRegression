CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp1

$(EXEC): main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o no.o
	$(CC) $(CFLAGS) main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o -o $(EXEC)

no-constante.o: arvore/no-constante.cpp
	$(CC) $(CFLAGS) -c arvore/no-constante.cpp -o no-constante.o

no-operacao-binaria.o: 
	$(CC) $(CFLAGS) -c arvore/no-operacao-binaria.cpp -o no-operacao-binaria.o

no-operacao-unaria.o: 
	$(CC) $(CFLAGS) -c arvore/no-operacao-unaria.cpp -o no-operacao-unaria.o

no-variavel.o: 
	$(CC) $(CFLAGS) -c arvore/no-variavel.cpp -o no-variavel.o

no.o: arvore/no.h

clean:
	rm -rf no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o