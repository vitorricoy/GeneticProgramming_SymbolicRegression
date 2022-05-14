#pragma once

#include <vector>
#include "../arvore/no.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"

class Genotipo
{
public:
    Genotipo(int n);
    Genotipo(int n, int inicio, std::vector<int> expr1, std::vector<int> expr2, std::vector<int> expr3, std::vector<int> expr4, std::vector<int> expr5, std::vector<int> expr6, std::vector<double> constante);
    Genotipo *recombinar(Genotipo *par);
    Genotipo *criarMutacao();
    Genotipo *criarCopia();
    No *converterEmArvore();

private:
    void mutar();
    int gerarRegraProducaoAleatoria(int numVariaveis);
    double gerarConstante();
    No *gerarArvore(int indices[7], int profundidade);

    int inicio;                    // 1 valor
    std::vector<int> expr1;        // 2 valores
    std::vector<int> expr2;        // 4 valores
    std::vector<int> expr3;        // 8 valores
    std::vector<int> expr4;        // 16 valores
    std::vector<int> expr5;        // 32 valores
    std::vector<int> expr6;        // 64 valores
    std::vector<double> constante; // 64 valores

    int numVariaveis;
};
