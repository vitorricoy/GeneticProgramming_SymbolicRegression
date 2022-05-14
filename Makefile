CC=g++
CFLAGS=-Wall -Wextra -Wno-unused-parameter -g -pthread -fsanitize=thread
EXEC=./tp1

$(EXEC): main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o no.o calculadora-fitness.o dados-treinamento.o genotipo.o genotipo-arvore.o aleatorio.o
	$(CC) $(CFLAGS) main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o calculadora-fitness.o dados-treinamento.o genotipo.o aleatorio.o genotipo-arvore.o -o $(EXEC)

no-constante.o: arvore/no-constante.cpp
	$(CC) $(CFLAGS) -c arvore/no-constante.cpp -o no-constante.o

no-operacao-binaria.o: 
	$(CC) $(CFLAGS) -c arvore/no-operacao-binaria.cpp -o no-operacao-binaria.o

no-operacao-unaria.o: 
	$(CC) $(CFLAGS) -c arvore/no-operacao-unaria.cpp -o no-operacao-unaria.o

no-variavel.o: 
	$(CC) $(CFLAGS) -c arvore/no-variavel.cpp -o no-variavel.o

no.o: arvore/no.h

calculadora-fitness.o: 
	$(CC) $(CFLAGS) -c fitness/calculadora-fitness.cpp -o calculadora-fitness.o

dados-treinamento.o: 
	$(CC) $(CFLAGS) -c fitness/dados-treinamento.cpp -o dados-treinamento.o

genotipo.o:
	$(CC) $(CFLAGS) -c genotipo/genotipo.cpp -o genotipo.o

genotipo-arvore.o:
	$(CC) $(CFLAGS) -c genotipo/genotipo-arvore.cpp -o genotipo-arvore.o

aleatorio.o:
	$(CC) $(CFLAGS) -c util/aleatorio.cpp -o aleatorio.o

clean:
	rm -rf no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o calculadora-fitness.o dados-treinamento.o genotipo.o genotipo-arvore.o aleatorio.o