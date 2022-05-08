#include "no-constante.h"
#include <vector>
#include <string>

NoConstante::NoConstante(Constante c)
{
    valorNo = c;
}

int NoConstante::numeroFilhos()
{
    return 0;
}

bool NoConstante::terminal()
{
    return true;
}

std::vector<No *> NoConstante::filhos()
{
    return std::vector<No *>();
}

double NoConstante::valor(std::vector<double> &variaveis)
{
    switch (valorNo)
    {
    case UM:
        return 1;
    case DOIS:
        return 2;
    case QUATRO:
        return 4;
    case OITO:
        return 8;
    case DEZESSEIS:
        return 16;
    case TRINTA_DOIS:
        return 32;
    default:
        return 0;
    }
}

std::string NoConstante::print()
{
    switch (valorNo)
    {
    case UM:
        return "1";
    case DOIS:
        return "2";
    case QUATRO:
        return "4";
    case OITO:
        return "8";
    case DEZESSEIS:
        return "16";
    case TRINTA_DOIS:
        return "32";
    default:
        return "0";
    }
}