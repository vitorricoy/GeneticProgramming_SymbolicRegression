#pragma once
#include "no.h"
#include <string>

enum OperacaoUnaria
{
    SENO,
    COSSENO,
    LOG
};

class NoOperacaoUnaria : public No
{
public:
    NoOperacaoUnaria(OperacaoUnaria o, No *f);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();

private:
    OperacaoUnaria valorNo;
    No *filho;
};