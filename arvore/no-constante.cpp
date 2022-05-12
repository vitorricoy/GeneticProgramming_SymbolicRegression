#include "no-constante.h"
#include <vector>
#include <string>

NoConstante::NoConstante(double c)
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
    return valorNo;
}

std::string NoConstante::print()
{
    return std::to_string(valorNo);
}

NoConstante::~NoConstante()
{
}