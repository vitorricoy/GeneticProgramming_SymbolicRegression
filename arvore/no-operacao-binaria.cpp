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
    tamSubArvore = calcularTamSubArvore(f1, f2);
    bloat = 0;
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
    bloat = 0;
    double v1 = filho1->valor(variaveis);
    double v2 = filho2->valor(variaveis);
    bloat += filho1->bloat;
    bloat += filho2->bloat;
    switch (valorNo)
    {
    case SOMA:
        if (v1 == 0)
        {
            bloat++;
        }
        if (v2 == 0)
        {
            bloat++;
        }
        return v1 + v2;
    case SUBTRACAO:
        if (v1 == 0)
        {
            bloat++;
        }
        if (v2 == 0)
        {
            bloat++;
        }
        return v1 - v2;
    case MULTIPLICACAO:
        if (v1 == 1)
        {
            bloat++;
        }
        if (v2 == 1)
        {
            bloat++;
        }
        return v1 * v2;
    case DIVISAO:
        if (v1 == 1)
        {
            bloat++;
        }
        if (v2 == 1)
        {
            bloat++;
        }
        return (v2 == 0 || (std::isinf(v1) && std::isinf(v2))) ? 1 : v1 / v2;
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

int NoOperacaoBinaria::calcularTamSubArvore(No *f1, No *f2)
{
    int alt1 = 1 + f1->tamSubArvore;
    int alt2 = 1 + f2->tamSubArvore;
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

TiposNo NoOperacaoBinaria::getTipo()
{
    return TiposNo::BINARIA;
}