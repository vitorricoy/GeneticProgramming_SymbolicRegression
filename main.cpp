#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>
#include <thread>
#include <set>
#include <mutex>
#include <iomanip>
#include <fstream>

#include "genotipo/genotipo.h"
#include "fitness/dados-treinamento.h"
#include "fitness/calculadora-fitness.h"
#include "util/aleatorio.h"
#include "programacao-genetica/programacao-genetica.h"

void executarAlgoritmo(DadosTreinamento *dadosTreinamento, CalculadoraFitness *calculadora, Parametros parametros)
{
    ProgramacaoGenetica *instancia = new ProgramacaoGenetica(calculadora, dadosTreinamento, parametros);
    instancia->executar();
    delete instancia;
}

int main(int argc, char **argv)
{
    double PM = 0.05;
    double PC = 0.9;
    int TAM_POP = 500;
    int NUM_GER = 500;
    int TAMANHO_TORNEIO = 3;
    int OPERADORES_ELITISTAS = 0;
    int ELITISMO = 1;
    std::string caminhoArquivo = "datasets/synth1/synth1-train.csv";
    if (argc == 8)
    {
        PM = atof(argv[1]);
        PC = atof(argv[2]);
        TAM_POP = atoi(argv[3]);
        NUM_GER = atoi(argv[4]);
        TAMANHO_TORNEIO = atoi(argv[5]);
        OPERADORES_ELITISTAS = atoi(argv[6]);
        ELITISMO = atoi(argv[7]);
        caminhoArquivo = std::string(argv[8]);
    }

    Parametros parametros(PM, PC, TAM_POP, NUM_GER, TAMANHO_TORNEIO, OPERADORES_ELITISTAS, ELITISMO);

    DadosTreinamento *dadosTreinamento = new DadosTreinamento(caminhoArquivo);
    CalculadoraFitness *calculadora = new CalculadoraFitness(dadosTreinamento);

    executarAlgoritmo(dadosTreinamento, calculadora, parametros);

    delete dadosTreinamento;
    delete calculadora;
    return 0;
}