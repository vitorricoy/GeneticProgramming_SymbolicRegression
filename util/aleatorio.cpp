#include "aleatorio.h"
#include <algorithm>

std::mt19937 Aleatorio::gerador = std::mt19937(static_cast<long unsigned int>((std::time(NULL))));

int Aleatorio::intAleatorio(int de, int ate)
{
    std::uniform_int_distribution<int> distr(de, ate);

    return distr(gerador);
}

double Aleatorio::doubleAleatorio(double de, double ate)
{
    std::uniform_real_distribution<double> distr(de, ate);
    return distr(gerador);
}

void Aleatorio::shuffle(int v[], int tam)
{
    std::shuffle(v, v + tam, gerador);
}