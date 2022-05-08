#pragma once
#include "dados-treinamento.h"
#include "../arvore/no.h"

class CalculadoraFitness
{
public:
    CalculadoraFitness(DadosTreinamento *d);
    double calcularFitness(No *individuo);

private:
    DadosTreinamento *dados;
};