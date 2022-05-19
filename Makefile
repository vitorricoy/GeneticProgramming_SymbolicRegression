CC=g++
CFLAGS=-Wall -Wextra -Wno-unused-parameter -pthread -g -fsanitize=thread
EXEC=./tp1

$(EXEC): main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o no.o calculadora-fitness.o dados-treinamento.o genotipo.o aleatorio.o programacao-genetica.o
	$(CC) $(CFLAGS) main.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o calculadora-fitness.o dados-treinamento.o genotipo.o aleatorio.o programacao-genetica.o -o $(EXEC)

experimentacao: experimentacao.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o no.o calculadora-fitness.o dados-treinamento.o genotipo.o aleatorio.o programacao-genetica.o
	$(CC) $(CFLAGS) experimentacao.cpp no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o calculadora-fitness.o dados-treinamento.o genotipo.o aleatorio.o programacao-genetica.o -o experimentacao

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

aleatorio.o:
	$(CC) $(CFLAGS) -c util/aleatorio.cpp -o aleatorio.o

programacao-genetica.o:
	$(CC) $(CFLAGS) -c programacao-genetica/programacao-genetica.cpp -o programacao-genetica.o

clean:
	rm -rf no-constante.o no-operacao-binaria.o no-operacao-unaria.o no-variavel.o calculadora-fitness.o programacao-genetica.o dados-treinamento.o genotipo.o aleatorio.o