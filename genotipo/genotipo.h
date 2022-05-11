#pragma once

#include <vector>
#include "../arvore/no.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"

class Genotipo
{
public:
    Genotipo(int n);
    Genotipo(int n, std::vector<int> inicio, std::vector<int> expr1, std::vector<int> expr2, std::vector<int> expr3, std::vector<int> operacoesBinarias, std::vector<int> operacoesUnarias);
    Genotipo *recombinar(Genotipo *par);
    void mutar();
    Genotipo *criarMutacao();
    No *converterEmArvore();

private:
    int gerarRegraProducaoAleatoria(int numVariaveis);
    double gerarConstante();
    No *gerarArvore(int indices[8]);

    int inicio; // 1 valor
    int expr1[2]; // 2 valores
    int expr2[4]; // 4 valores
    int expr3[8]; // 8 valores
    int expr4[16]; // 16 valores
    int expr5[32]; // 32 valores
    int expr6[64]; // 64 valores
    double constante[64]; // 64 valores
    
    int numVariaveis;
};
