#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>
#include <thread>

#include "genotipo/genotipo.h"
#include "fitness/dados-treinamento.h"
#include "fitness/calculadora-fitness.h"
#include "util/aleatorio.h"

#define PM 0.3
#define PR 0.69
#define TAM_POP 10
#define NUM_GER 10

double fitness[TAM_POP];
Genotipo *individuos[2][TAM_POP];
CalculadoraFitness *calculadora;
int indiceIndividuos[TAM_POP];
bool operadoresElitistas = true;

int tamanhoTorneio = 3;

void atualizarFitnessThread(unsigned i, int geracao)
{
    fitness[i] = calculadora->calcularFitness(individuos[geracao % 2][i]);
}

void atualizarFitness(int geracao)
{
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < TAM_POP; i++)
    {
        threads.emplace_back(atualizarFitnessThread, i, geracao);
    }

    for (std::thread &t : threads)
    {
        t.join();
    }
}

int selecionaUm()
{
    Aleatorio::shuffle(indiceIndividuos, TAM_POP);
    double fitnessMelhor = std::numeric_limits<double>::max();
    int indiceMelhor = indiceIndividuos[0];
    ;
    for (int j = 0; j < tamanhoTorneio; j++)
    {
        if (fitness[indiceIndividuos[j]] < fitnessMelhor)
        {
            fitnessMelhor = fitness[indiceIndividuos[j]];
            indiceMelhor = indiceIndividuos[j];
        }
    }
    return indiceMelhor;
}

void selecao(unsigned i, int geracao)
{
    if (Aleatorio::doubleAleatorio(0, 1) < PR)
    {
        int indPai = selecionaUm();
        int indMae = selecionaUm();
        //  Seleciona
        Genotipo *pai = individuos[geracao % 2][indPai];
        Genotipo *mae = individuos[geracao % 2][indMae];

        Genotipo *filho = pai->recombinar(mae);

        if (operadoresElitistas)
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
        Genotipo *individuo = individuos[geracao % 2][indIndividuo];
        if (Aleatorio::doubleAleatorio(0, 1) < PM)
        {
            Genotipo *mutacao = individuo->criarMutacao();
            if (operadoresElitistas)
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

int main()
{
    DadosTreinamento *dadosTreinamento = new DadosTreinamento("datasets/synth1/synth1-train.csv");
    calculadora = new CalculadoraFitness(dadosTreinamento);
    for (int i = 0; i < TAM_POP; i++)
    {
        Genotipo *novo = new Genotipo(dadosTreinamento->dimensao());
        individuos[0][i] = novo;
        indiceIndividuos[i] = i;
    }
    std::vector<double> todasFitness;
    for (int geracao = 0; geracao < NUM_GER; geracao++)
    {
        atualizarFitness(geracao);
        std::vector<std::thread> threads;
        for (unsigned i = 0; i < TAM_POP; i++)
        {
            threads.emplace_back(selecao, i, geracao);
        }

        for (std::thread &t : threads)
        {
            t.join();
        }

        for (Genotipo *&g : individuos[geracao % 2])
        {
            delete g;
        }
    }
    atualizarFitness(NUM_GER);
    int indMelhor = -1;
    double fitnessMelhor = std::numeric_limits<double>::max();
    for (unsigned i = 0; i < TAM_POP; i++)
    {
        if (fitnessMelhor > fitness[i])
        {
            fitnessMelhor = fitness[i];
            indMelhor = i;
        }
    }
    No *arvore = individuos[NUM_GER % 2][indMelhor]->converterEmArvore();
    std::cout << arvore->print() << "\n";
    std::cout << fitnessMelhor << "\n";
    delete arvore;

    for (Genotipo *&g : individuos[NUM_GER % 2])
    {
        delete g;
    }

    delete dadosTreinamento;
    delete calculadora;
    return 0;
}