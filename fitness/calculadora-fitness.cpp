#include <cmath>
#include <iostream>

#include "calculadora-fitness.h"
#include "dados-treinamento.h"
#include "../arvore/no.h"
#include "../genotipo/genotipo-arvore.h"

CalculadoraFitness::CalculadoraFitness(DadosTreinamento *d)
{
    dados = d;
}
double CalculadoraFitness::calcularFitness(GenotipoArvore *genotipo)
{
    No *individuo = genotipo->obterRaiz();
    std::vector<std::pair<std::vector<double>, double>> dadosTreino = dados->dados();
    double somatorioNumerador = 0.0;
    double somatorioValoresReais = 0.0;

    for (std::pair<std::vector<double>, double> casoTreino : dadosTreino)
    {
        double valorPrevisto = individuo->valor(casoTreino.first);
        double valorReal = casoTreino.second;
        somatorioNumerador += (valorReal - valorPrevisto) * (valorReal - valorPrevisto);
        somatorioValoresReais += valorReal;
    }

    double mediaValoresReais = somatorioValoresReais / dadosTreino.size();

    double somatorioDenominador = 0.0;
    for (unsigned i = 0; i < dadosTreino.size(); i++)
    {
        somatorioDenominador += (dadosTreino[i].second - mediaValoresReais) * (dadosTreino[i].second - mediaValoresReais);
    }

    if (somatorioDenominador == 0)
    {
        somatorioDenominador = 1;
    }
    if (std::isinf(somatorioNumerador) && std::isinf(somatorioDenominador))
    {
        return somatorioNumerador;
    }
    return std::sqrt(somatorioNumerador / somatorioDenominador);
}