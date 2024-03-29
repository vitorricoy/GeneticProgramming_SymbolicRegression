#include "no-variavel.h"

NoVariavel::NoVariavel(Variavel v)
{
    noPai = nullptr;
    valorNo = v;
    tamSubArvore = calcularTamSubArvore();
}

int NoVariavel::numeroFilhos()
{
    return 0;
}

bool NoVariavel::terminal()
{
    return true;
}

std::vector<No *> NoVariavel::filhos()
{
    return std::vector<No *>();
}

double NoVariavel::valor(std::vector<double> &variaveis)
{
    return variaveis[valorNo];
}

std::string NoVariavel::print()
{
    switch (valorNo)
    {
    case A:
        return "A";
    case B:
        return "B";
    case C:
        return "C";
    case D:
        return "D";
    case E:
        return "E";
    case F:
        return "F";
    case G:
        return "G";
    case H:
        return "H";
    case I:
        return "I";
    case J:
        return "J";
    case K:
        return "K";
    case L:
        return "L";
    case M:
        return "M";
    case N:
        return "N";
    case O:
        return "O";
    case P:
        return "P";
    case Q:
        return "Q";
    case R:
        return "R";
    case S:
        return "S";
    case T:
        return "T";
    case U:
        return "U";
    case V:
        return "V";
    case W:
        return "W";
    case X:
        return "X";
    case Y:
        return "Y";
    case Z:
        return "Z";
    default:
        return "0";
    }
}

NoVariavel::~NoVariavel()
{
}

int NoVariavel::calcularTamSubArvore()
{
    return 1;
}

No *NoVariavel::pai()
{
    return noPai;
}

void NoVariavel::setPai(No *p)
{
    noPai = p;
}

Variavel NoVariavel::conteudoNo()
{
    return valorNo;
}

TiposNo NoVariavel::getTipo()
{
    return TiposNo::VARIAVEL;
}