#pragma once
#include "no.h"
#include <string>

enum OperacaoUnaria
{
    SENO,
    COSSENO,
    INV,
    EXP,
    LOG
};

class NoOperacaoUnaria : public No
{
public:
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    NoOperacaoUnaria(OperacaoUnaria o, No *f);

private:
    OperacaoUnaria valorNo;
    No *filho;
};