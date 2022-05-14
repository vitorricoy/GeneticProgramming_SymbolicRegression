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
    NoOperacaoBinaria(OperacaoBinaria o, No *f1, No *f2);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    int calcularAltura(No *f1, No *f2);
    ~NoOperacaoBinaria();
    No *pai();
    void setPai(No *p);
    OperacaoBinaria conteudoNo();
    void setFilho1(No *f);
    void setFilho2(No *f);

private:
    OperacaoBinaria valorNo;
    No *filho1;
    No *filho2;
    No *noPai;
};