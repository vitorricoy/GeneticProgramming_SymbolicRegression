#pragma once
#include "dados-treinamento.h"
#include "../arvore/no.h"
#include "../genotipo/genotipo.h"

class CalculadoraFitness
{
public:
    CalculadoraFitness(DadosTreinamento *d);
    double calcularFitness(Genotipo *genotipo);

private:
    DadosTreinamento *dados;
};