#include "no-operacao-unaria.h"
#include <vector>
#include <limits>
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
    case LOG:
        return v == 0 ? -std::numeric_limits<double>::infinity() : std::log(std::abs(v));
    case ABS:
    	return std::abs(v);
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
    case ABS:
    	op = "abs";
    	break;
    default:
        op = "ERRO";
    }

    return op + "(" + filho->print() + ")";
}
