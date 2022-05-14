#include "aleatorio.h"
#include <algorithm>
#include <mutex>

std::mt19937 Aleatorio::gerador = std::mt19937(static_cast<long unsigned int>((std::time(NULL))));
std::mutex Aleatorio::mutex;

int Aleatorio::intAleatorio(int de, int ate)
{
    mutex.lock();
    std::uniform_int_distribution<int> distr(de, ate);
    int valor = distr(gerador);
    mutex.unlock();
    return valor;
}

double Aleatorio::doubleAleatorio(double de, double ate)
{
    mutex.lock();
    std::uniform_real_distribution<double> distr(de, ate);
    double valor = distr(gerador);
    mutex.unlock();
    return valor;
}

void Aleatorio::shuffle(int v[], int tam)
{
    mutex.lock();
    std::shuffle(v, v + tam, gerador);
    mutex.unlock();
}