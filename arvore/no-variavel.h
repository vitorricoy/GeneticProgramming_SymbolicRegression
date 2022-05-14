#pragma once
#include "no.h"
#include <string>

enum Variavel
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

class NoVariavel : public No
{
public:
    NoVariavel(Variavel v);
    int numeroFilhos();
    bool terminal();
    std::vector<No *> filhos();
    double valor(std::vector<double> &variaveis);
    std::string print();
    int calcularAltura();
    ~NoVariavel();
    No *pai();
    void setPai(No *p);
    Variavel conteudoNo();

private:
    Variavel valorNo;
    No *noPai;
};