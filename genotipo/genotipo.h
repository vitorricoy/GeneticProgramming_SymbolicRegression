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
    std::pair<Genotipo *, Genotipo *> recombinar(Genotipo *par);
    void mutar();
    Genotipo *criarMutacao();
    No *converterEmArvore();

private:
    int gerarRegraProducaoAleatoria(int numVariaveis);
    No *gerarInicio(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);
    No *gerarExpr1(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);
    No *gerarExpr2(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);
    No *gerarExpr3(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);
    OperacaoBinaria gerarOpBin(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);
    OperacaoUnaria gerarOpUn(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin);

    std::vector<int> inicio;
    std::vector<int> expr1;
    std::vector<int> expr2;
    std::vector<int> expr3;
    std::vector<int> operacoesBinarias;
    std::vector<int> operacoesUnarias;
    int numVariaveis;
};