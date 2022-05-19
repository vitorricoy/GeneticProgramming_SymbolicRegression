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

void executarAlgoritmo(DadosTreinamento *dadosTreinamento, int iter, CalculadoraFitness *calculadora, Parametros parametros)
{
    ProgramacaoGenetica *instancia = new ProgramacaoGenetica(calculadora, dadosTreinamento, parametros);
    instancia->executar();
    std::vector<Estatistica> estatisticas = instancia->obterEstatisticas();

    std::string caminhoArquivo = "output/saida" + std::to_string(parametros.PM) + "_" + std::to_string(parametros.PC) + "_" + std::to_string(parametros.TAM_POP) + "_" +
                                 std::to_string(parametros.NUM_GER) + "_" + std::to_string(parametros.TAMANHO_TORNEIO) + "_" + std::to_string(parametros.OPERADORES_ELITISTAS) +
                                 "_" + std::to_string(parametros.ELITISMO) + ".csv";
    std::ifstream arquivoExistente(caminhoArquivo, std::ios::binary);
    if (!arquivoExistente)
    {
        // Arquivo não existe
        std::ofstream saida(caminhoArquivo, std::ios_base::app);
        if (saida.is_open())
        {
            saida << "PM = " << parametros.PM << ", PC = " << parametros.PC << ", TAM_POP = " << parametros.TAM_POP << ", NUM_GER = " << parametros.NUM_GER << ", tamTorneio = " << parametros.TAMANHO_TORNEIO << ", operElitistas = " << parametros.OPERADORES_ELITISTAS << ", ELITISMO = " << parametros.ELITISMO << "\n";
            saida << "iteracao,geracao,idt individuo,fitness,individuos melhores que media dos pais,individuos piores que media dos pais,numero cruzamentos,numero mutacoes\n";
            for (unsigned j = 0; j < estatisticas.size(); j++)
            {
                Estatistica e = estatisticas[j];
                for (int i = 0; i < parametros.TAM_POP; i++)
                {
                    saida << std::fixed << std::setprecision(5) << iter << "," << j << "," << i << "," << e.fitnesses[i] << "," << e.individuosMelhoresQueMediaDosPais << "," << e.individuosPioresQueMediaDosPais
                          << "," << e.numeroCruzamentos << "," << e.numeroMutacoes << "\n";
                }
            }
            saida.close();
        }
    }
    else
    {
        std::ofstream saida(caminhoArquivo, std::ios_base::app);
        if (saida.is_open())
        {
            for (unsigned j = 0; j < estatisticas.size(); j++)
            {
                Estatistica e = estatisticas[j];
                for (int i = 0; i < parametros.TAM_POP; i++)
                {
                    saida << std::fixed << std::setprecision(5) << iter << "," << j << "," << i << "," << e.fitnesses[i] << "," << e.individuosMelhoresQueMediaDosPais << "," << e.individuosPioresQueMediaDosPais
                          << "," << e.numeroCruzamentos << "," << e.numeroMutacoes << "\n";
                }
            }
            saida.close();
        }
    }
    delete instancia;
}

int main(int argc, char **argv)
{
    double PM = 0.05;
    double PC = 0.9;
    int TAM_POP = 50;
    int NUM_GER = 50;
    int TAMANHO_TORNEIO = 3;
    int OPERADORES_ELITISTAS = 0;
    int ELITISMO = 1;
    std::string caminhoArquivo = "datasets/synth1/synth1-train.csv";

    Parametros parametros(PM, PC, TAM_POP, NUM_GER, TAMANHO_TORNEIO, OPERADORES_ELITISTAS, ELITISMO);

    DadosTreinamento *dadosTreinamento = new DadosTreinamento(caminhoArquivo);
    CalculadoraFitness *calculadora = new CalculadoraFitness(dadosTreinamento);

    for (int tp = 0; tp < 1; tp++)
    {
        if (tp == 0)
        {
            TAM_POP = 50;
        }
        if (tp == 1)
        {
            TAM_POP = 100;
        }
        if (tp == 2)
        {
            TAM_POP = 500;
        }
        for (int ng = 0; ng < 1; ng++)
        {
            if (ng == 0)
            {
                NUM_GER = 50;
            }
            if (ng == 1)
            {
                NUM_GER = 100;
            }
            if (ng == 2)
            {
                NUM_GER = 500;
            }
            for (int i = 0; i < 1; i++)
            {
                executarAlgoritmo(dadosTreinamento, i, calculadora, parametros);
            }
        }
    }

    delete dadosTreinamento;
    delete calculadora;
    return 0;
}