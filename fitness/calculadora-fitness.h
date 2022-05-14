#pragma once
#include "dados-treinamento.h"
#include "../arvore/no.h"
#include "../genotipo/genotipo-arvore.h"

class CalculadoraFitness
{
public:
    CalculadoraFitness(DadosTreinamento *d);
    double calcularFitness(GenotipoArvore *genotipo);

private:
    DadosTreinamento *dados;
};