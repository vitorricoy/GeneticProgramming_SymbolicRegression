#pragma once
#include "no.h"
#include <string>

class NoConstante : public No
{
public:
    NoConstante(double c);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();

private:
    double valorNo;
};
