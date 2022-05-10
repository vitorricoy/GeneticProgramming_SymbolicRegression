#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

#include "genotipo/genotipo.h"
#include "fitness/dados-treinamento.h"
#include "fitness/calculadora-fitness.h"

#define PM 5
#define TAM_POP 500
#define NUM_GER 500

std::vector<double> fitness;
std::vector<Genotipo *> individuos;
CalculadoraFitness *calculadora;
std::vector<int> indiceIndividuos;
std::mt19937 generator(static_cast<long unsigned int>((std::time(NULL))));
bool operadoresElitistas = false;

int tamanhoTorneio = 3;

void atualizarFitness()
{
    fitness.clear();
    for (unsigned i = 0; i < individuos.size(); i++)
    {
        fitness.push_back(calculadora->calcularFitness(individuos[i]->converterEmArvore()));
    }
}

std::pair<int, int> selecionaPais()
{
    std::shuffle(indiceIndividuos.begin(), indiceIndividuos.end(), generator);
    double fitnessMelhor1 = std::numeric_limits<double>::max();
    int indiceMelhor1 = indiceIndividuos.front();
    for (int j = 0; j < tamanhoTorneio; j++)
    {
        if (fitness[indiceIndividuos[j]] < fitnessMelhor1)
        {
            fitnessMelhor1 = fitness[indiceIndividuos[j]];
            indiceMelhor1 = indiceIndividuos[j];
        }
    }
    std::shuffle(indiceIndividuos.begin(), indiceIndividuos.end(), generator);
    double fitnessMelhor2 = std::numeric_limits<double>::max();
    int indiceMelhor2 = indiceIndividuos.front();
    for (int j = 0; j < tamanhoTorneio; j++)
    {
        if (indiceMelhor1 != indiceIndividuos[j] && fitness[indiceIndividuos[j]] < fitnessMelhor2)
        {
            fitnessMelhor2 = fitness[indiceIndividuos[j]];
            indiceMelhor2 = indiceIndividuos[j];
        }
    }
    return {indiceMelhor1, indiceMelhor2};
}

int selecionaUm()
{
    std::shuffle(indiceIndividuos.begin(), indiceIndividuos.end(), generator);
    double fitnessMelhor = std::numeric_limits<double>::max();
    int indiceMelhor = -1;
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

int main()
{
    srand(std::time(NULL));
    individuos = std::vector<Genotipo *>();
    DadosTreinamento *dadosTreinamento = new DadosTreinamento("datasets/synth1/synth1-train.csv");
    calculadora = new CalculadoraFitness(dadosTreinamento);

    for (int i = 0; i < TAM_POP; i++)
    {
        Genotipo *novo = new Genotipo(dadosTreinamento->dimensao());
        individuos.push_back(novo);
        indiceIndividuos.push_back(i);
    }
    atualizarFitness();
    std::vector<double> todasFitness;
    for (int geracoes = 0; geracoes < NUM_GER; geracoes++)
    {
        std::vector<Genotipo *> novaPopulacao;
        // Realiza selecoes até encher população
        for (int i = 0; i < TAM_POP; i++)
        {
            if (rand() % 100 < PM)
            {
                int individuo = selecionaUm();
                Genotipo *mutacao = individuos[individuo]->criarMutacao();
                if (operadoresElitistas)
                {
                    double fitnessMutacao = calculadora->calcularFitness(mutacao->converterEmArvore());
                    if (fitnessMutacao <= fitness[individuo])
                    {
                        novaPopulacao.push_back(mutacao);
                    }
                    else
                    {
                        novaPopulacao.push_back(individuos[individuo]);
                    }
                }
                else
                {
                    novaPopulacao.push_back(mutacao);
                }
            }
            else
            {
                std::pair<int, int> paiMae = selecionaPais();
                //  std::cout << paiMae.first << " " << paiMae.second << std::endl;
                //  Seleciona
                Genotipo *pai = individuos[paiMae.first];
                Genotipo *mae = individuos[paiMae.second];

                Genotipo *filho = pai->recombinar(mae);

                if (operadoresElitistas)
                {
                    // Implementa operadores elitistas
                    std::vector<std::pair<double, Genotipo *>> opcoes;
                    opcoes.push_back({fitness[paiMae.first], pai});
                    opcoes.push_back({fitness[paiMae.second], mae});

                    double fitnessFilho = calculadora->calcularFitness(filho->converterEmArvore());
                    opcoes.push_back({fitnessFilho, filho});

                    std::sort(opcoes.begin(), opcoes.end());
                    novaPopulacao.push_back(opcoes[0].second);
                }
                else
                {
                    novaPopulacao.push_back(filho);
                }
            }
        }
        while (novaPopulacao.size() > individuos.size())
        {
            novaPopulacao.pop_back();
        }
        individuos.clear();
        individuos = novaPopulacao;

        atualizarFitness();
    }
    double v = 0.0;
    for (double f : fitness)
    {
        v += f;
    }
    todasFitness.push_back(v / fitness.size());
    int indMelhor = -1;
    double fitnessMelhor = std::numeric_limits<double>::max();
    for (unsigned i = 0; i < fitness.size(); i++)
    {
        if (fitnessMelhor > fitness[i])
        {
            fitnessMelhor = fitness[i];
            indMelhor = i;
        }
    }
    std::cout << individuos[indMelhor]->converterEmArvore()->print() << "\n";
    std::cout << fitnessMelhor << "\n";
    return 0;
}