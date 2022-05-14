#pragma once
#include <random>
#include <ctime>
#include <vector>
#include <mutex>

class Aleatorio
{
public:
    static int intAleatorio(int de, int ate);
    static double doubleAleatorio(double de, double ate);
    static void shuffle(int v[], int tam);

private:
    static std::mt19937 gerador;
    static std::mutex mutex;
};