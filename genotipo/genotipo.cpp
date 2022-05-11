#include <iostream>

#include "genotipo.h"
#include "../arvore/no.h"
#include "../arvore/no-constante.h"
#include "../arvore/no-variavel.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"

Genotipo::Genotipo(int n)
{
    numVariaveis = n;
    int numTerminais = n+1;

    /*inicio.push_back(gerarRegraProducaoAleatoria(n));

    expr1.push_back(gerarRegraProducaoAleatoria(n));
    expr1.push_back(gerarRegraProducaoAleatoria(n));

    expr2.push_back(gerarRegraProducaoAleatoria(n));
    expr2.push_back(gerarRegraProducaoAleatoria(n));
    expr2.push_back(gerarRegraProducaoAleatoria(n));
    expr2.push_back(gerarRegraProducaoAleatoria(n));

    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);
    expr3.push_back(rand() % numTerminais);

    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);
    operacoesBinarias.push_back(rand() % 5);

    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    operacoesUnarias.push_back(rand() % 4);
    
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());
    constante.push_back(gerarConstante());*/
}

Genotipo::Genotipo(int n, std::vector<int> inicio, std::vector<int> expr1, std::vector<int> expr2, std::vector<int> expr3, std::vector<int> operacoesBinarias, std::vector<int> operacoesUnarias)
{
    numVariaveis = n;
    this->inicio = inicio;
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
    this->operacoesBinarias = operacoesBinarias;
    this->operacoesUnarias = operacoesUnarias;
}

double Genotipo::gerarConstante() {
    double multiplicador = 1;
    if (rand()%2) {
        multiplicador = -1;
    }
    return multiplicador * ((double)rand()/(double)RAND_MAX);
}

int Genotipo::gerarRegraProducaoAleatoria(int numVariaveis)
{
    int numTerminais = numVariaveis + 1;
    int op = rand() % 3;
    if (op == 0)
    {
        // Binaria
        return 0;
    }
    if (op == 1)
    {
        // Unaria
        return 1;
    }
    return 2 + (rand() % numTerminais);
}

Genotipo *Genotipo::recombinar(Genotipo *par)
{
    int mascara = 1 + (rand() % 62);
    std::vector<int> inicio = this->inicio;
    std::vector<int> expr1 = this->expr1;
    std::vector<int> expr2 = this->expr2;
    std::vector<int> expr3 = this->expr3;
    std::vector<int> operacoesBinarias = this->operacoesBinarias;
    std::vector<int> operacoesUnarias = this->operacoesUnarias;

    if (mascara & 1)
    {
        operacoesUnarias = par->operacoesUnarias;
    }

    if (mascara & 2)
    {
        operacoesBinarias = par->operacoesBinarias;
    }

    if (mascara & 4)
    {
        expr3 = par->expr3;
    }

    if (mascara & 8)
    {
        expr2 = par->expr3;
    }

    if (mascara & 16)
    {
        expr1 = par->expr3;
    }

    if (mascara & 32)
    {
        inicio = par->inicio;
    }

    return new Genotipo(this->numVariaveis, inicio, expr1, expr2, expr3, operacoesBinarias, operacoesUnarias);
}

Genotipo *Genotipo::criarMutacao()
{
    Genotipo *novoIndividuo = new Genotipo(numVariaveis, inicio, expr1, expr2, expr3, operacoesBinarias, operacoesUnarias);
    novoIndividuo->mutar();
    return novoIndividuo;
}

void Genotipo::mutar()
{
    int op1 = rand() % 6;
    switch (op1)
    {
    case 0:
        inicio[0] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 1:
        expr1[rand() % 2] = gerarRegraProducaoAleatoria(numVariaveis);
        break;

    case 2:
        expr2[rand() % 4] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 3:
        expr3[rand() % 8] = rand() % (numVariaveis + 6);
        break;
    case 4:
        operacoesBinarias[rand() % 7] = rand() % 5;
        break;
    default:
        operacoesUnarias[rand() % 7] = rand() % 4;
        break;
    }
}

No *Genotipo::converterEmArvore()
{
    int indices[] = {0, 0, 0, 0, 0, 0, 0, 0};
    return gerarArvore(indices);
}

No *gerarArvore(int indices[8])
{
    /*int producao = inicio[indInicio];
    indInicio++;
    if (producao == 0)
    {
        OperacaoBinaria opBin = gerarOpBin(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho1 = gerarExpr1(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho2 = gerarExpr1(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoBinaria(opBin, filho1, filho2);
    }
    if (producao == 1)
    {
        OperacaoUnaria opUn = gerarOpUn(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho = gerarExpr1(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoUnaria(opUn, filho);
    }
    producao -= 2;
    if (producao >= numVariaveis)
    {
        producao -= numVariaveis;
        return new NoConstante(Constante(producao));
    }
    return new NoVariavel(Variavel(producao));*/
}
