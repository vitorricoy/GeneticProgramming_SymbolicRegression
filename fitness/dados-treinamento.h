#pragma once
#include <string>
#include <vector>
#include <utility>

class DadosTreinamento
{
public:
    DadosTreinamento(std::string arquivo);
    std::vector<std::pair<std::vector<double>, double>> dados();
    int dimensao();

private:
    std::vector<std::pair<std::vector<double>, double>> dadosLidos;
    int dimensaoDados;
};