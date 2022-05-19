#include "../arvore/no.h"
#include <vector>

#pragma once

class Genotipo
{
public:
    Genotipo(int n);
    Genotipo(int n, No *raiz);
    Genotipo *recombinar(Genotipo *par);
    Genotipo *criarMutacao();
    Genotipo *criarCopia();
    No *obterRaiz();
    void preencherListaNos(No *noAtual);
    void preencherListaNos(No *noAtual, std::vector<No *> &nos);
    ~Genotipo();
    No *copiarArvore(No *noAtual);

private:
    No *mutar();
    No *gerarArvoreAleatoria(int numVar, int profundidade);
    No *raiz;
    int numeroVariaveis;
    std::vector<No *> nos;
};