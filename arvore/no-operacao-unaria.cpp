#include "no-operacao-unaria.h"
#include <vector>
#include <limits>
#include <cmath>

NoOperacaoUnaria::NoOperacaoUnaria(OperacaoUnaria o, No *f)
{
    noPai = nullptr;
    valorNo = o;
    filho = f;
    tamSubArvore = calcularTamSubArvore(f);
}

int NoOperacaoUnaria::numeroFilhos()
{
    return 1;
}

bool NoOperacaoUnaria::terminal()
{
    return false;
}

std::vector<No *> NoOperacaoUnaria::filhos()
{
    return {filho};
}

double NoOperacaoUnaria::valor(std::vector<double> &variaveis)
{
    double v = filho->valor(variaveis);

    switch (valorNo)
    {
    case SENO:
        return std::isinf(v) ? 0 : std::sin(v);
    case COSSENO:
        return std::isinf(v) ? 0 : std::cos(v);
    case LOG:
        return v == 0 ? 0 : std::log(std::abs(v));
    case EXP:
        return std::exp(v);
    default:
        return 0;
    }
}

std::string NoOperacaoUnaria::print()
{
    std::string op;
    switch (valorNo)
    {
    case SENO:
        op = "sen";
        break;
    case COSSENO:
        op = "cos";
        break;
    case LOG:
        op = "ln";
        break;
    case EXP:
        op = "exp";
        break;
    default:
        op = "ERRO";
    }

    return op + "(" + filho->print() + ")";
}

NoOperacaoUnaria::~NoOperacaoUnaria()
{
    delete filho;
}

int NoOperacaoUnaria::calcularTamSubArvore(No *f)
{
    return 1 + f->tamSubArvore;
}

No *NoOperacaoUnaria::pai()
{
    return noPai;
}

void NoOperacaoUnaria::setPai(No *p)
{
    noPai = p;
}

OperacaoUnaria NoOperacaoUnaria::conteudoNo()
{
    return valorNo;
}

void NoOperacaoUnaria::setFilho(No *f)
{
    filho = f;
}

TiposNo NoOperacaoUnaria::getTipo()
{
    return TiposNo::UNARIA;
}