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
    TRINTA_DOIS,
    SESSENTA_QUATRO,
    CENTO_VINTE_OITO
};

class NoConstante : public No
{
public:
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    NoConstante(Constante c);

private:
    Constante valorNo;
};