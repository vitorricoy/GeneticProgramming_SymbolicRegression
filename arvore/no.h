#pragma once
#include <vector>
#include <string>

enum TiposNo
{
    BINARIA,
    UNARIA,
    CONSTANTE,
    VARIAVEL
};

class No
{
public:
    No()
    {
        std::vector<int> oi();
    }
    virtual int numeroFilhos() = 0;
    virtual bool terminal() = 0;
    virtual std::vector<No *> filhos() = 0;
    virtual double valor(std::vector<double> &variaveis) = 0;
    virtual std::string print() = 0;
    virtual No *pai() = 0;
    virtual TiposNo getTipo() = 0;
    virtual ~No() {}
    int tamSubArvore;
    virtual void setPai(No *p) = 0;
};