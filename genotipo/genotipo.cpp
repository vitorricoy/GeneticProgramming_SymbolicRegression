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
    int numTerminais = n + 6;

    inicio.clear();
    expr1.clear();
    expr2.clear();
    expr3.clear();
    operacoesUnarias.clear();
    operacoesBinarias.clear();

    inicio.push_back(gerarRegraProducaoAleatoria(n));

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

    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);
    operacoesBinarias.push_back(rand() % 4);

    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
    operacoesUnarias.push_back(rand() % 5);
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

int Genotipo::gerarRegraProducaoAleatoria(int numVariaveis)
{
    int numTerminais = numVariaveis + 6;
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

std::pair<Genotipo *, Genotipo *> Genotipo::recombinar(Genotipo *par)
{
    int mascara = 1 + (rand() % 7);
    std::vector<int> inicio1 = this->inicio;
    std::vector<int> expr11 = this->expr1;
    std::vector<int> expr21 = this->expr2;
    std::vector<int> expr31 = this->expr3;
    std::vector<int> operacoesBinarias1 = this->operacoesBinarias;
    std::vector<int> operacoesUnarias1 = this->operacoesUnarias;

    std::vector<int> inicio2 = par->inicio;
    std::vector<int> expr12 = par->expr1;
    std::vector<int> expr22 = par->expr2;
    std::vector<int> expr32 = par->expr3;
    std::vector<int> operacoesBinarias2 = par->operacoesBinarias;
    std::vector<int> operacoesUnarias2 = par->operacoesUnarias;

    if (mascara & 1)
    {
        operacoesUnarias1.swap(operacoesUnarias2);
    }

    if (mascara & 2)
    {
        operacoesBinarias1.swap(operacoesBinarias2);
    }

    if (mascara & 4)
    {
        expr31.swap(expr32);
    }

    return std::make_pair(
        new Genotipo(this->numVariaveis, inicio1, expr11, expr21, expr31, operacoesBinarias1, operacoesUnarias1),
        new Genotipo(this->numVariaveis, inicio2, expr12, expr22, expr32, operacoesBinarias2, operacoesUnarias2));
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
        operacoesBinarias[rand() % 7] = rand() % 4;
        break;
    default:
        operacoesUnarias[rand() % 7] = rand() % 5;
        break;
    }
}

No *Genotipo::converterEmArvore()
{
    int indInicio = 0, indExpr1 = 0, indExpr2 = 0, indExpr3 = 0, indOpUn = 0, indOpBin = 0;
    return gerarInicio(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
}

No *Genotipo::gerarInicio(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int producao = inicio[indInicio];
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
    return new NoVariavel(Variavel(producao));
}

No *Genotipo::gerarExpr1(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int producao = expr1[indExpr1];
    indExpr1++;
    if (producao == 0)
    {
        OperacaoBinaria opBin = gerarOpBin(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho1 = gerarExpr2(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho2 = gerarExpr2(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoBinaria(opBin, filho1, filho2);
    }
    if (producao == 1)
    {
        OperacaoUnaria opUn = gerarOpUn(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho = gerarExpr2(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoUnaria(opUn, filho);
    }
    producao -= 2;
    if (producao >= numVariaveis)
    {
        producao -= numVariaveis;
        return new NoConstante(Constante(producao));
    }
    return new NoVariavel(Variavel(producao));
}

No *Genotipo::gerarExpr2(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int producao = expr2[indExpr2];
    indExpr2++;
    if (producao == 0)
    {
        OperacaoBinaria opBin = gerarOpBin(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho1 = gerarExpr3(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho2 = gerarExpr3(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoBinaria(opBin, filho1, filho2);
    }
    if (producao == 1)
    {
        OperacaoUnaria opUn = gerarOpUn(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        No *filho = gerarExpr3(indInicio, indExpr1, indExpr2, indExpr3, indOpUn, indOpBin);
        return new NoOperacaoUnaria(opUn, filho);
    }
    producao -= 2;
    if (producao >= numVariaveis)
    {
        producao -= numVariaveis;
        return new NoConstante(Constante(producao));
    }
    return new NoVariavel(Variavel(producao));
}

No *Genotipo::gerarExpr3(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int producao = expr3[indExpr3];
    indExpr3++;
    if (producao >= numVariaveis)
    {
        producao -= numVariaveis;
        return new NoConstante(Constante(producao));
    }
    return new NoVariavel(Variavel(producao));
}

OperacaoBinaria Genotipo::gerarOpBin(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int opBin = operacoesBinarias[indOpBin];
    indOpBin++;
    return OperacaoBinaria(opBin);
}

OperacaoUnaria Genotipo::gerarOpUn(int &indInicio, int &indExpr1, int &indExpr2, int &indExpr3, int &indOpUn, int &indOpBin)
{
    int opUn = operacoesUnarias[indOpUn];
    indOpUn++;
    return OperacaoUnaria(opUn);
}
