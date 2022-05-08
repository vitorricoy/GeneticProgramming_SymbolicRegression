#pragma once
#include "no.h"
#include <string>

enum OperacaoBinaria
{
    SOMA,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO
};

class NoOperacaoBinaria : public No
{
public:
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    NoOperacaoBinaria(OperacaoBinaria o, No *f1, No *f2);

private:
    OperacaoBinaria valorNo;
    No *filho1;
    No *filho2;
};