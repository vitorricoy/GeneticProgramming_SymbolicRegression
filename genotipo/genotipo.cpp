#include <iostream>

#include "genotipo.h"
#include "../arvore/no.h"
#include "../arvore/no-constante.h"
#include "../arvore/no-variavel.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"
#include "../util/aleatorio.h"

#define NUM_OP_BIN 4
#define NUM_OP_UN 4

Genotipo::Genotipo(int n)
{
    numVariaveis = n;
    int numTerminais = n + 1;

    inicio = gerarRegraProducaoAleatoria(n);

    for (int i = 0; i < 2; i++)
    {
        expr1.push_back(gerarRegraProducaoAleatoria(n));
    }

    for (int i = 0; i < 4; i++)
    {
        expr2.push_back(gerarRegraProducaoAleatoria(n));
    }

    for (int i = 0; i < 8; i++)
    {
        expr3.push_back(gerarRegraProducaoAleatoria(n));
    }

    for (int i = 0; i < 16; i++)
    {
        expr4.push_back(gerarRegraProducaoAleatoria(n));
    }

    for (int i = 0; i < 32; i++)
    {
        expr5.push_back(gerarRegraProducaoAleatoria(n));
    }

    for (int i = 0; i < 64; i++)
    {
        expr6.push_back(Aleatorio::intAleatorio(0, numTerminais - 1));
    }

    for (int i = 0; i < 64; i++)
    {
        constante.push_back(gerarConstante());
    }
}

Genotipo::Genotipo(int n, int inicio, std::vector<int> expr1, std::vector<int> expr2, std::vector<int> expr3, std::vector<int> expr4, std::vector<int> expr5, std::vector<int> expr6, std::vector<double> constante)
{
    numVariaveis = n;
    this->inicio = inicio;
    this->expr1 = expr1;
    this->expr2 = expr2;
    this->expr3 = expr3;
    this->expr4 = expr4;
    this->expr5 = expr5;
    this->expr6 = expr6;
    this->constante = constante;
}

double Genotipo::gerarConstante()
{
    return Aleatorio::doubleAleatorio(-1, 1);
}

int Genotipo::gerarRegraProducaoAleatoria(int numVariaveis)
{
    int numTerminais = numVariaveis + 10;
    return Aleatorio::intAleatorio(0, numTerminais - 1);
}

Genotipo *Genotipo::recombinar(Genotipo *par)
{
    int mascara = Aleatorio::intAleatorio(1, 255);
    int novoInicio = inicio;
    std::vector<int> novaExpr1 = expr1;
    std::vector<int> novaExpr2 = expr2;
    std::vector<int> novaExpr3 = expr3;
    std::vector<int> novaExpr4 = expr4;
    std::vector<int> novaExpr5 = expr5;
    std::vector<int> novaExpr6 = expr6;
    std::vector<double> novaConstante = constante;

    if (mascara & 1)
    {
        novaConstante = par->constante;
    }

    if (mascara & 2)
    {
        novaExpr6 = par->expr6;
    }

    if (mascara & 4)
    {
        novaExpr5 = par->expr5;
    }

    if (mascara & 8)
    {
        novaExpr4 = par->expr4;
    }

    if (mascara & 16)
    {
        novaExpr3 = par->expr3;
    }

    if (mascara & 32)
    {
        novaExpr2 = par->expr2;
    }

    if (mascara & 64)
    {
        novaExpr1 = par->expr1;
    }

    if (mascara & 128)
    {
        novoInicio = par->inicio;
    }

    return new Genotipo(this->numVariaveis, novoInicio, novaExpr1, novaExpr2, novaExpr3, novaExpr4, novaExpr5, novaExpr6, novaConstante);
}

Genotipo *Genotipo::criarMutacao()
{
    Genotipo *novoIndividuo = new Genotipo(numVariaveis, inicio, expr1, expr2, expr3, expr4, expr5, expr6, constante);
    novoIndividuo->mutar();
    return novoIndividuo;
}

Genotipo *Genotipo::criarCopia()
{
    Genotipo *novoIndividuo = new Genotipo(numVariaveis, inicio, expr1, expr2, expr3, expr4, expr5, expr6, constante);
    return novoIndividuo;
}

void Genotipo::mutar()
{
    int op1 = Aleatorio::intAleatorio(0, 7);
    switch (op1)
    {
    case 0:
        inicio = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 1:
        expr1[Aleatorio::intAleatorio(0, 1)] = gerarRegraProducaoAleatoria(numVariaveis);
        break;

    case 2:
        expr2[Aleatorio::intAleatorio(0, 3)] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 3:
        expr3[Aleatorio::intAleatorio(0, 7)] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 4:
        expr4[Aleatorio::intAleatorio(0, 15)] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 5:
        expr5[Aleatorio::intAleatorio(0, 31)] = gerarRegraProducaoAleatoria(numVariaveis);
        break;
    case 6:
        expr6[Aleatorio::intAleatorio(0, 63)] = Aleatorio::intAleatorio(0, numVariaveis + 1);
        break;
    default:
        constante[Aleatorio::intAleatorio(0, 63)] = gerarConstante();
        break;
    }
}

No *Genotipo::converterEmArvore()
{
    int indices[] = {0, 0, 0, 0, 0, 0, 0};
    return gerarArvore(indices, 0);
}

No *Genotipo::gerarArvore(int indices[7], int profundidade)
{
    if (profundidade == 6)
    {
        int producao = expr6[indices[5]];
        indices[5]++;
        if (producao < numVariaveis)
        {
            return new NoVariavel(Variavel(producao));
        }
        double valorConstante = constante[indices[6]];
        indices[6]++;
        return new NoConstante(valorConstante);
    }
    else
    {
        int producao;
        switch (profundidade)
        {
        case 0:
            producao = inicio;
            break;
        case 1:
            producao = expr1[indices[0]];
            indices[0]++;
            break;
        case 2:
            producao = expr2[indices[1]];
            indices[1]++;
            break;
        case 3:
            producao = expr3[indices[2]];
            indices[2]++;
            break;
        case 4:
            producao = expr4[indices[3]];
            indices[3]++;
            break;
        default:
            producao = expr5[indices[4]];
            indices[4]++;
            break;
        }
        if (producao >= 0 && producao <= 3)
        {
            No *filho1 = gerarArvore(indices, profundidade + 1);
            No *filho2 = gerarArvore(indices, profundidade + 1);
            return new NoOperacaoBinaria(OperacaoBinaria(producao), filho1, filho2);
        }
        if (producao >= 4 && producao <= 7)
        {
            No *filho = gerarArvore(indices, profundidade + 1);
            return new NoOperacaoUnaria(OperacaoUnaria(producao - 4), filho);
        }
        if (producao >= 8 && producao < 8 + numVariaveis)
        {
            return new NoVariavel(Variavel(producao - 8));
        }
        double valorConstante = constante[indices[6]];
        indices[6]++;
        return new NoConstante(valorConstante);
    }
}
