#pragma once
#include <vector>
#include <string>

class No
{
public:
    virtual int numeroFilhos() = 0;
    virtual bool terminal() = 0;
    virtual std::vector<No *> filhos() = 0;
    virtual double valor(std::vector<double> &variaveis) = 0;
    virtual std::string print() = 0;
};