#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

#include "dados-treinamento.h"

DadosTreinamento::DadosTreinamento(std::string arquivo)
{
    std::vector<std::vector<std::string>> conteudo;
    std::vector<std::string> linha;
    std::string linhaArquivo, palavra;

    std::fstream file(arquivo, std::ios::in);
    if (file.is_open())
    {
        while (getline(file, linhaArquivo))
        {

            linha.clear();

            std::stringstream str(linhaArquivo);

            while (getline(str, palavra, ','))
            {
                linha.push_back(palavra);
            }
            conteudo.push_back(linha);
        }
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo\n";
    }
    dadosLidos.clear();
    for (std::vector<std::string> v : conteudo)
    {
        std::vector<double> variaveis;
        for (unsigned i = 0; i < v.size() - 1; i++)
        {
            variaveis.push_back(std::stod(v[i]));
        }

        double valor = std::stod(v.back());
        dadosLidos.push_back(std::make_pair(variaveis, valor));
    }
    dimensaoDados = dadosLidos.front().first.size();
}

std::vector<std::pair<std::vector<double>, double>> DadosTreinamento::dados()
{
    return dadosLidos;
}

int DadosTreinamento::dimensao()
{
    return dimensaoDados;
}