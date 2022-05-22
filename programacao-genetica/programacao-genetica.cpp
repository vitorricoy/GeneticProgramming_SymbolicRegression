#include <thread>
#include <iostream>
#include <cstring>
#include <iomanip>

#include "programacao-genetica.h"
#include "../util/aleatorio.h"

ProgramacaoGenetica::ProgramacaoGenetica(CalculadoraFitness *calculadora, DadosTreinamento *dadosTreinamento, Parametros parametros) : selecaoMutex(), estatisticaMutex()
{
    memset(fitness, 0, sizeof(fitness));
    memset(individuos, 0, sizeof(individuos));
    memset(indiceIndividuos, 0, sizeof(indiceIndividuos));
    estatisticas.clear();
    mutacaoMelhorQueMediaDosPais = 0;
    mutacaoPiorQueMediaDosPais = 0;
    cruzamentoMelhorQueMediaDosPais = 0;
    cruzamentoPiorQueMediaDosPais = 0;
    numeroCruzamentos = 0;
    numeroMutacoes = 0;

    this->calculadora = calculadora;
    this->parametros = parametros;
    std::cout << std::fixed << std::setprecision(5);
    for (int i = 0; i < parametros.TAM_POP; i++)
    {
        Genotipo *novo = new Genotipo(dadosTreinamento->dimensao());
        individuos[0][i] = novo;
        indiceIndividuos[i] = i;
    }
}

ProgramacaoGenetica::~ProgramacaoGenetica()
{
    for (Genotipo *&g : individuos[parametros.NUM_GER % 2])
    {
        delete g;
    }
}

std::vector<Estatistica> ProgramacaoGenetica::obterEstatisticas()
{
    return estatisticas;
}

void ProgramacaoGenetica::selecaoOperacao(int geracao)
{
    std::vector<std::thread> threads;
    mutacaoMelhorQueMediaDosPais = 0;
    mutacaoPiorQueMediaDosPais = 0;
    cruzamentoMelhorQueMediaDosPais = 0;
    cruzamentoPiorQueMediaDosPais = 0;
    numeroCruzamentos = 0;
    numeroMutacoes = 0;
    for (int i = 0; i < parametros.TAM_POP - parametros.ELITISMO; i++)
    {
        threads.emplace_back(&ProgramacaoGenetica::selecaoOperacaoThread, this, i, geracao);
    }

    for (std::thread &t : threads)
    {
        t.join();
    }
    if (parametros.ELITISMO)
    {
        Genotipo *melhorIndividuo = individuos[geracao % 2][0];
        double fitnessMelhor = fitness[0];
        for (int i = 1; i < parametros.TAM_POP; i++)
        {
            if (fitness[i] < fitnessMelhor)
            {
                fitnessMelhor = fitness[i];
                melhorIndividuo = individuos[geracao % 2][i];
            }
        }
        individuos[(geracao + 1) % 2][parametros.TAM_POP - 1] = melhorIndividuo->criarCopia();
    }
}

Genotipo *ProgramacaoGenetica::executar()
{
    for (int geracao = 0; geracao < parametros.NUM_GER; geracao++)
    {
        atualizarFitness(geracao);
        selecaoOperacao(geracao);

        for (Genotipo *&g : individuos[geracao % 2])
        {
            delete g;
        }
    }
    atualizarFitness(parametros.NUM_GER);
    int indMelhor = -1;
    double fitnessMelhor = std::numeric_limits<double>::max();
    for (int i = 0; i < parametros.TAM_POP; i++)
    {
        if (fitnessMelhor > fitness[i])
        {
            fitnessMelhor = fitness[i];
            indMelhor = i;
        }
    }
    No *arvore = individuos[parametros.NUM_GER % 2][indMelhor]->obterRaiz();
    std::cout << arvore->print() << "\n";
    std::cout << fitnessMelhor << "\n";
    return individuos[parametros.NUM_GER % 2][indMelhor];
}

void ProgramacaoGenetica::atualizarFitnessThread(unsigned i, int geracao)
{
    fitness[i] = calculadora->calcularFitness(individuos[geracao % 2][i]);
}

void ProgramacaoGenetica::atualizarFitness(int geracao)
{
    std::vector<std::thread> threads;
    for (int i = 0; i < parametros.TAM_POP; i++)
    {
        threads.emplace_back(&ProgramacaoGenetica::atualizarFitnessThread, this, i, geracao);
    }

    for (std::thread &t : threads)
    {
        t.join();
    }

    std::vector<double> fitnesses;
    double bloatSoma = 0.0;
    int individuosComBloat = 0;
    for (int i = 0; i < parametros.TAM_POP; i++)
    {
        if (individuos[geracao % 2][i]->obterRaiz()->bloat)
        {
            bloatSoma += individuos[geracao % 2][i]->obterRaiz()->bloat;
            individuosComBloat++;
        }
        fitnesses.push_back(fitness[i]);
    }
    bloatSoma /= (double)individuosComBloat;
    estatisticas.emplace_back(fitnesses, mutacaoMelhorQueMediaDosPais, mutacaoPiorQueMediaDosPais, cruzamentoMelhorQueMediaDosPais, cruzamentoPiorQueMediaDosPais, numeroCruzamentos, numeroMutacoes, bloatSoma, individuosComBloat);
}

int ProgramacaoGenetica::selecionaUm()
{
    selecaoMutex.lock();
    Aleatorio::shuffle(indiceIndividuos, parametros.TAM_POP);
    double fitnessMelhor = std::numeric_limits<double>::max();
    int indiceMelhor = indiceIndividuos[0];
    for (int j = 0; j < parametros.TAMANHO_TORNEIO; j++)
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

void ProgramacaoGenetica::selecaoOperacaoThread(unsigned i, int geracao)
{
    if (Aleatorio::doubleAleatorio(0, 1) < parametros.PC)
    {
        estatisticaMutex.lock();
        numeroCruzamentos++;
        estatisticaMutex.unlock();
        int indPai = selecionaUm();
        int indMae = selecionaUm();
        Genotipo *pai = individuos[geracao % 2][indPai];
        Genotipo *mae = individuos[geracao % 2][indMae];

        Genotipo *filho = pai->recombinar(mae);
        double fitnessFilho = calculadora->calcularFitness(filho);

        if (fitnessFilho < (fitness[indPai] + fitness[indMae]) / 2.0)
        {
            estatisticaMutex.lock();
            cruzamentoMelhorQueMediaDosPais++;
            estatisticaMutex.unlock();
        }
        else if (fitnessFilho > (fitness[indPai] + fitness[indMae]) / 2.0)
        {
            estatisticaMutex.lock();
            cruzamentoPiorQueMediaDosPais++;
            estatisticaMutex.unlock();
        }

        if (parametros.OPERADORES_ELITISTAS)
        {
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
        if (Aleatorio::doubleAleatorio(0, 1) < parametros.PM)
        {
            estatisticaMutex.lock();
            numeroMutacoes++;
            estatisticaMutex.unlock();
            Genotipo *mutacao = individuo->criarMutacao();

            double fitnessMutacao = calculadora->calcularFitness(mutacao);
            if (fitnessMutacao < fitness[indIndividuo])
            {
                estatisticaMutex.lock();
                mutacaoMelhorQueMediaDosPais++;
                estatisticaMutex.unlock();
            }
            else if (fitnessMutacao > fitness[indIndividuo])
            {
                estatisticaMutex.lock();
                mutacaoPiorQueMediaDosPais++;
                estatisticaMutex.unlock();
            }
            if (parametros.OPERADORES_ELITISTAS)
            {
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