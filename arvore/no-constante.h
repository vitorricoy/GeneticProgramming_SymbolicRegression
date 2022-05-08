#pragma once
#include "no.h"
#include <string>

enum Constante
{
    UM,
    DOIS,
    QUATRO,
    OITO,
    DEZESSEIS,
    TRINTA_DOIS
};

class NoConstante : public No
{
public:
    NoConstante(Constante c);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();

private:
    Constante valorNo;
};