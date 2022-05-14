#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>
#include <thread>
#include <mutex>

#include "genotipo/genotipo-arvore.h"
#include "fitness/dados-treinamento.h"
#include "fitness/calculadora-fitness.h"
#include "util/aleatorio.h"

double PM = 0.5;
double PR = 0.5;
int TAM_POP = 100;
int NUM_GER = 100;
int TAMANHO_TORNEIO = 2;
int OPERADORES_ELITISTAS = 0;

double fitness[1000];
GenotipoArvore *individuos[2][1000];
CalculadoraFitness *calculadora;
int indiceIndividuos[1000];
std::mutex selecaoMutex;

void atualizarFitnessThread(unsigned i, int geracao)
{
    fitness[i] = calculadora->calcularFitness(individuos[geracao % 2][i]);
}

void atualizarFitness(int geracao)
{
    std::vector<std::thread> threads;
    for (int i = 0; i < TAM_POP; i++)
    {
        threads.emplace_back(atualizarFitnessThread, i, geracao);
        // atualizarFitnessThread(i, geracao);
    }

    for (std::thread &t : threads)
    {
        t.join();
    }
}

int selecionaUm()
{
    selecaoMutex.lock();
    Aleatorio::shuffle(indiceIndividuos, TAM_POP);
    double fitnessMelhor = std::numeric_limits<double>::max();
    int indiceMelhor = indiceIndividuos[0];
    for (int j = 0; j < TAMANHO_TORNEIO; j++)
    {
        if (fitness[indiceIndividuos[j]] < fitnessMelhor)
        {
            fitnessMelhor = fitness[indiceIndividuos[j]];
            indiceMelhor = indiceIndividuos[j];
        }
    }
    selecaoMutex.unlock();
    return indiceMelhor;
}

void selecao(unsigned i, int geracao)
{
    if (Aleatorio::doubleAleatorio(0, 1) < PR)
    {
        int indPai = selecionaUm();
        int indMae = selecionaUm();
        //  Seleciona
        GenotipoArvore *pai = individuos[geracao % 2][indPai];
        GenotipoArvore *mae = individuos[geracao % 2][indMae];

        GenotipoArvore *filho = pai->recombinar(mae);

        if (OPERADORES_ELITISTAS)
        {
            // Implementa operadores elitistas
            double fitnessFilho = calculadora->calcularFitness(filho);
            if (fitnessFilho <= fitness[indPai] && fitnessFilho <= fitness[indMae])
            {
                individuos[(geracao + 1) % 2][i] = filho;
            }
            else
            {
                delete filho;
                if (fitness[indPai] <= fitness[indMae])
                {
                    individuos[(geracao + 1) % 2][i] = pai->criarCopia();
                }
                else
                {
                    individuos[(geracao + 1) % 2][i] = mae->criarCopia();
                }
            }
        }
        else
        {
            individuos[(geracao + 1) % 2][i] = filho;
        }
    }
    else
    {
        int indIndividuo = selecionaUm();
        GenotipoArvore *individuo = individuos[geracao % 2][indIndividuo];
        if (Aleatorio::doubleAleatorio(0, 1) < PM)
        {
            GenotipoArvore *mutacao = individuo->criarMutacao();
            if (OPERADORES_ELITISTAS)
            {
                double fitnessMutacao = calculadora->calcularFitness(mutacao);
                if (fitnessMutacao <= fitness[indIndividuo])
                {
                    individuos[(geracao + 1) % 2][i] = mutacao;
                }
                else
                {
                    individuos[(geracao + 1) % 2][i] = individuo->criarCopia();
                    delete mutacao;
                }
            }
            else
            {
                individuos[(geracao + 1) % 2][i] = mutacao;
            }
        }
        else
        {
            individuos[(geracao + 1) % 2][i] = individuo->criarCopia();
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 7)
    {
        PM = atof(argv[1]);
        PR = atof(argv[2]);
        TAM_POP = atoi(argv[3]);
        NUM_GER = atoi(argv[4]);
        TAMANHO_TORNEIO = atoi(argv[5]);
        OPERADORES_ELITISTAS = atoi(argv[6]);
    }

    std::cout << PM << " " << PR << " " << TAM_POP << " " << NUM_GER << " " << TAMANHO_TORNEIO << " " << OPERADORES_ELITISTAS << std::endl;

    DadosTreinamento *dadosTreinamento = new DadosTreinamento("datasets/synth1/synth1-train.csv");
    calculadora = new CalculadoraFitness(dadosTreinamento);
    for (int i = 0; i < TAM_POP; i++)
    {
        GenotipoArvore *novo = new GenotipoArvore(dadosTreinamento->dimensao());
        individuos[0][i] = novo;
        indiceIndividuos[i] = i;
    }
    std::vector<double> todasFitness;
    for (int geracao = 0; geracao < NUM_GER; geracao++)
    {
        atualizarFitness(geracao);
        std::vector<std::thread> threads;
        for (int i = 0; i < TAM_POP; i++)
        {
            // selecao(i, geracao);
            threads.emplace_back(selecao, i, geracao);
        }

        for (std::thread &t : threads)
        {
            t.join();
        }

        for (GenotipoArvore *&g : individuos[geracao % 2])
        {
            delete g;
        }
    }
    atualizarFitness(NUM_GER);
    int indMelhor = -1;
    double fitnessMelhor = std::numeric_limits<double>::max();
    for (int i = 0; i < TAM_POP; i++)
    {
        if (fitnessMelhor > fitness[i])
        {
            fitnessMelhor = fitness[i];
            indMelhor = i;
        }
    }
    No *arvore = individuos[NUM_GER % 2][indMelhor]->obterRaiz();
    std::cout << arvore->print() << "\n";
    std::cout << fitnessMelhor << "\n";

    for (GenotipoArvore *&g : individuos[NUM_GER % 2])
    {
        delete g;
    }

    delete dadosTreinamento;
    delete calculadora;
    return 0;
}