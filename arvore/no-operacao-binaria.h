#pragma once
#include "no.h"
#include <string>

enum OperacaoBinaria
{
    SOMA,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,
    EXPONENCIACAO
};

class NoOperacaoBinaria : public No
{
public:
    NoOperacaoBinaria(OperacaoBinaria o, No *f1, No *f2);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    ~NoOperacaoBinaria();

private:
    OperacaoBinaria valorNo;
    No *filho1;
    No *filho2;
};