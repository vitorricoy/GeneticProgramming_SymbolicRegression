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
    int calcularAltura();
    ~NoConstante();
    No *pai();
    void setPai(No *p);
    double conteudoNo();

private:
    double valorNo;
    No *noPai;
};
