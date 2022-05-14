#include "no-operacao-binaria.h"
#include <vector>
#include <limits>
#include <cmath>

NoOperacaoBinaria::NoOperacaoBinaria(OperacaoBinaria o, No *f1, No *f2)
{
    noPai = nullptr;
    valorNo = o;
    filho1 = f1;
    filho2 = f2;
    altura = calcularAltura(f1, f2);
}

int NoOperacaoBinaria::numeroFilhos()
{
    return 2;
}

bool NoOperacaoBinaria::terminal()
{
    return false;
}

std::vector<No *> NoOperacaoBinaria::filhos()
{
    return {filho1, filho2};
}

double NoOperacaoBinaria::valor(std::vector<double> &variaveis)
{
    double v1 = filho1->valor(variaveis);
    double v2 = filho2->valor(variaveis);

    switch (valorNo)
    {
    case SOMA:
        return v1 + v2;
    case SUBTRACAO:
        return v1 - v2;
    case MULTIPLICACAO:
        return v1 * v2;
    case DIVISAO:
        return v2 == 0 ? 1 : v1 / v2;
    default:
        return 0;
    }
}

std::string NoOperacaoBinaria::print()
{
    std::string op;
    switch (valorNo)
    {
    case SOMA:
        op = "+";
        break;
    case SUBTRACAO:
        op = "-";
        break;
    case MULTIPLICACAO:
        op = "*";
        break;
    case DIVISAO:
        op = "/";
        break;
    default:
        op = "ERRO";
    }

    return "(" + filho1->print() + " " + op + " " + filho2->print() + ")";
}

NoOperacaoBinaria::~NoOperacaoBinaria()
{
    delete filho1;
    delete filho2;
}

int NoOperacaoBinaria::calcularAltura(No *f1, No *f2)
{
    int alt1 = 1 + f1->altura;
    int alt2 = 1 + f2->altura;
    if (alt1 > alt2)
    {
        return alt1;
    }
    return alt2;
}

No *NoOperacaoBinaria::pai()
{
    return noPai;
}

void NoOperacaoBinaria::setPai(No *p)
{
    noPai = p;
}

OperacaoBinaria NoOperacaoBinaria::conteudoNo()
{
    return valorNo;
}

void NoOperacaoBinaria::setFilho1(No *f)
{
    filho1 = f;
}

void NoOperacaoBinaria::setFilho2(No *f)
{
    filho2 = f;
}