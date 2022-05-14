#pragma once
#include "no.h"
#include <string>

enum OperacaoUnaria
{
    SENO,
    COSSENO,
    LOG,
    EXP
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
    int calcularAltura(No *filho);
    ~NoOperacaoUnaria();
    No *pai();
    void setPai(No *p);
    OperacaoUnaria conteudoNo();
    void setFilho(No *f);

private:
    OperacaoUnaria valorNo;
    No *filho;
    No *noPai;
};
