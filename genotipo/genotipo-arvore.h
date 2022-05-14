#include "../arvore/no.h"
#include <vector>

#pragma once

class GenotipoArvore
{
public:
    GenotipoArvore(int n);
    GenotipoArvore(int n, No *raiz);
    GenotipoArvore *recombinar(GenotipoArvore *par);
    GenotipoArvore *criarMutacao();
    GenotipoArvore *criarCopia();
    No *obterRaiz();
    void preencherListaNos(No *noAtual);
    void preencherListaNos(No *noAtual, std::vector<No *> &nos);
    ~GenotipoArvore();
    No *copiarArvore(No *noAtual);

private:
    void mutar();
    No *gerarArvoreAleatoria(int numVar, int profundidade);
    No *raiz;
    int numeroVariaveis;
    std::vector<No *> nos;
};