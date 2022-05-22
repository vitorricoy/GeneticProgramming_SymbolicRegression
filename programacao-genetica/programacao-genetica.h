#pragma once
#include <vector>
#include <mutex>
#include "../genotipo/genotipo.h"
#include "../fitness/calculadora-fitness.h"

struct Estatistica
{
    std::vector<double> fitnesses;
    int mutacaoMelhorQueMediaDosPais;
    int mutacaoPiorQueMediaDosPais;
    int cruzamentoMelhorQueMediaDosPais;
    int cruzamentoPiorQueMediaDosPais;
    int numeroCruzamentos;
    int numeroMutacoes;
    double bloat;
    int individuosComBloat;

    Estatistica(std::vector<double> f, int mM, int mP, int cM, int cP, int nC, int nM, double b, int icb) : fitnesses(f), mutacaoMelhorQueMediaDosPais(mM), mutacaoPiorQueMediaDosPais(mP), cruzamentoMelhorQueMediaDosPais(cM), cruzamentoPiorQueMediaDosPais(cP), numeroCruzamentos(nC), numeroMutacoes(nM), bloat(b), individuosComBloat(icb)
    {
    }
};

struct Parametros
{
    double PM;
    double PC;
    int TAM_POP;
    int NUM_GER;
    int TAMANHO_TORNEIO;
    int OPERADORES_ELITISTAS;
    int ELITISMO;

    Parametros()
    {
        PM = 0.05;
        PC = 0.9;
        TAM_POP = 50;
        NUM_GER = 50;
        TAMANHO_TORNEIO = 3;
        OPERADORES_ELITISTAS = 0;
        ELITISMO = 1;
    }

    Parametros(double pm, double pc, int tamPop, int numGer, int tamTor, int operElit, int elitismo) : PM(pm), PC(pc), TAM_POP(tamPop), NUM_GER(numGer), TAMANHO_TORNEIO(tamTor), OPERADORES_ELITISTAS(operElit), ELITISMO(elitismo)
    {
    }
};

class ProgramacaoGenetica
{
public:
    ProgramacaoGenetica(CalculadoraFitness *calculadora, DadosTreinamento *dadosTreinamento, Parametros parametros);
    ~ProgramacaoGenetica();
    Genotipo *executar();
    std::vector<Estatistica> obterEstatisticas();

private:
    void atualizarFitnessThread(unsigned i, int geracao);
    void atualizarFitness(int geracao);
    void selecaoOperacao(int geracao);
    int selecionaUm();
    void selecaoOperacaoThread(unsigned i, int geracao);

    double fitness[1000];
    Genotipo *individuos[2][1000];
    CalculadoraFitness *calculadora;
    int indiceIndividuos[1000];
    std::mutex selecaoMutex;
    std::mutex estatisticaMutex;

    std::vector<Estatistica> estatisticas;
    int mutacaoMelhorQueMediaDosPais;
    int mutacaoPiorQueMediaDosPais;
    int cruzamentoMelhorQueMediaDosPais;
    int cruzamentoPiorQueMediaDosPais;
    int numeroCruzamentos;
    int numeroMutacoes;
    Parametros parametros;
};