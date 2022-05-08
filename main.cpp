#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "arvore/no.h"
#include "arvore/no-constante.h"
#include "arvore/no-variavel.h"
#include "arvore/no-operacao-binaria.h"
#include "arvore/no-operacao-unaria.h"

int numeroVariaveis = 3;

No *gerarArvore(int &naoTerminais)
{
    int aleatorio = rand() % 100;
    if (aleatorio < 15 * naoTerminais)
    {
        // Gera terminal
        if (rand() % 2 == 0)
        {
            // Constante
            int idtConstante = rand() % 8;
            return new NoConstante(Constante(idtConstante));
        }
        else
        {
            // Variavel
            int idtVariavel = rand() % numeroVariaveis;
            return new NoVariavel(Variavel(idtVariavel));
        }
    }
    else
    {
        // Gera nao terminal
        naoTerminais++;
        if (rand() % 2 == 0)
        {
            // Unario
            int idtUnario = rand() % 5;
            return new NoOperacaoUnaria(OperacaoUnaria(idtUnario), gerarArvore(naoTerminais));
        }
        else
        {
            // Binario
            int idtBinario = rand() % 4;
            return new NoOperacaoBinaria(OperacaoBinaria(idtBinario), gerarArvore(naoTerminais), gerarArvore(naoTerminais));
        }
    }
}

int main()
{
    srand(std::time(NULL));
    for (int i = 0; i < 15; i++)
    {
        int tam = 0;
        No *arv = gerarArvore(tam);
        std::cout << arv->print() << std::endl;
    }
}