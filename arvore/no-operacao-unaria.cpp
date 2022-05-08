#include "no-operacao-unaria.h"
#include <vector>
#include <cmath>

NoOperacaoUnaria::NoOperacaoUnaria(OperacaoUnaria o, No *f)
{
    valorNo = o;
    filho = f;
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
        return std::sin(v);
    case COSSENO:
        return std::cos(v);
    case INV:
        return 1.0 / v;
    case EXP:
        return std::exp(v);
    case LOG:
        return std::log(v);
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
    case INV:
        op = "inv";
        break;
    case EXP:
        op = "exp";
        break;
    case LOG:
        op = "ln";
        break;
    default:
        op = "ERRO";
    }

    return op + "(" + filho->print() + ")";
}

std::string getOp(OperacaoUnaria op)
{
    switch (op)
    {
    case SENO:
        return "sen";
    case COSSENO:
        return "cos";
    case INV:
        return "inv";
    case EXP:
        return "exp";
    case LOG:
        return "ln";
    default:
        return "ERRO";
    }
}