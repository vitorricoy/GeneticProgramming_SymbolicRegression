#include "no-operacao-binaria.h"
#include <vector>
#include <cmath>

NoOperacaoBinaria::NoOperacaoBinaria(OperacaoBinaria o, No *f1, No *f2)
{
    valorNo = o;
    filho1 = f1;
    filho2 = f2;
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
        return v2 == 0 ? 0 : v1 / v2;
    case EXPONENCIACAO:
        return std::pow(v1, v2);
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
    case EXPONENCIACAO:
        op = "^";
        break;
    default:
        op = "ERRO";
    }

    return "(" + filho1->print() + " " + op + " " + filho2->print() + ")";
}