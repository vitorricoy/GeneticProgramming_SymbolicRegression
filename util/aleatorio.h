#pragma once
#include <random>
#include <ctime>
#include <vector>

class Aleatorio
{
public:
    static int intAleatorio(int de, int ate);
    static double doubleAleatorio(double de, double ate);
    static void shuffle(int v[], int tam);

private:
    static std::mt19937 gerador;
};