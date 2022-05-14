#include "no-constante.h"
#include <vector>
#include <string>

NoConstante::NoConstante(double c)
{
    noPai = nullptr;
    valorNo = c;
    tamSubArvore = calcularTamSubArvore();
}

int NoConstante::numeroFilhos()
{
    return 0;
}

bool NoConstante::terminal()
{
    return true;
}

std::vector<No *> NoConstante::filhos()
{
    return std::vector<No *>();
}

double NoConstante::valor(std::vector<double> &variaveis)
{
    return valorNo;
}

std::string NoConstante::print()
{
    return std::to_string(valorNo);
}

NoConstante::~NoConstante()
{
}

int NoConstante::calcularTamSubArvore()
{
    return 1;
}

No *NoConstante::pai()
{
    return noPai;
}

void NoConstante::setPai(No *p)
{
    noPai = p;
}

double NoConstante::conteudoNo()
{
    return valorNo;
}

TiposNo NoConstante::getTipo()
{
    return TiposNo::CONSTANTE;
}