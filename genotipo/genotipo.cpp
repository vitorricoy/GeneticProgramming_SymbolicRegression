#include <iostream>
#include <vector>

#include "genotipo.h"
#include "../util/aleatorio.h"
#include "../arvore/no.h"
#include "../arvore/no-constante.h"
#include "../arvore/no-variavel.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"

#define NUM_OP_BIN 4
#define NUM_OP_UN 3

Genotipo::Genotipo(int n)
{
    numeroVariaveis = n;
    raiz = gerarArvoreAleatoria(n, 0);
    preencherListaNos(raiz);
}

No *Genotipo::gerarArvoreAleatoria(int numVar, int profundidade)
{
    if (profundidade == 6)
    {
        // Gera só constante ou variavel
        int constanteOuVariavel = Aleatorio::intAleatorio(0, numVar);
        if (constanteOuVariavel < numVar)
        {
            // Variavel
            No *no = new NoVariavel(Variavel(Aleatorio::intAleatorio(0, numVar - 1)));
            return no;
        }
        else
        {
            No *no = new NoConstante(Aleatorio::doubleAleatorio(-1, 1));
            return no;
        }
    }

    int operacaoBinOperacaoUnConstanteOuVariavel = Aleatorio::intAleatorio(0, NUM_OP_BIN + NUM_OP_UN + numVar);
    if (operacaoBinOperacaoUnConstanteOuVariavel >= 0 && operacaoBinOperacaoUnConstanteOuVariavel < NUM_OP_BIN)
    {
        No *f1 = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *f2 = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *no = new NoOperacaoBinaria(OperacaoBinaria(Aleatorio::intAleatorio(0, NUM_OP_BIN - 1)), f1, f2);
        f1->setPai(no);
        f2->setPai(no);
        return no;
    }
    if (operacaoBinOperacaoUnConstanteOuVariavel >= NUM_OP_BIN && operacaoBinOperacaoUnConstanteOuVariavel < NUM_OP_BIN + NUM_OP_UN)
    {
        No *f = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *no = new NoOperacaoUnaria(OperacaoUnaria(Aleatorio::intAleatorio(0, NUM_OP_UN - 1)), f);
        f->setPai(no);
        return no;
    }
    if (operacaoBinOperacaoUnConstanteOuVariavel >= NUM_OP_BIN + NUM_OP_UN && operacaoBinOperacaoUnConstanteOuVariavel < NUM_OP_BIN + NUM_OP_UN + numVar)
    {
        No *no = new NoVariavel(Variavel(Aleatorio::intAleatorio(0, numVar - 1)));
        return no;
    }
    No *no = new NoConstante(Aleatorio::doubleAleatorio(-1, 1));
    return no;
}

Genotipo::Genotipo(int n, No *r)
{
    numeroVariaveis = n;
    raiz = r;
    preencherListaNos(r);
}

void Genotipo::preencherListaNos(No *noAtual)
{
    nos.push_back(noAtual);
    for (unsigned i = 0; i < noAtual->filhos().size(); i++)
    {
        preencherListaNos(noAtual->filhos()[i]);
    }
}

void Genotipo::preencherListaNos(No *noAtual, std::vector<No *> &listaNos)
{
    listaNos.push_back(noAtual);
    for (unsigned i = 0; i < noAtual->filhos().size(); i++)
    {
        preencherListaNos(noAtual->filhos()[i], listaNos);
    }
}

Genotipo *Genotipo::recombinar(Genotipo *par)
{
    No *copia = copiarArvore(raiz);
    std::vector<No *> nosCopia;
    preencherListaNos(copia, nosCopia);
    No *escolhido1 = nosCopia[Aleatorio::intAleatorio(0, nosCopia.size() - 1)];
    No *temp = escolhido1;
    int nivel = -1;
    while (temp != nullptr)
    {
        nivel++;
        temp = temp->pai();
    }
    int tamMax = 7 - nivel;
    std::vector<No *> possiveis;
    for (No *n : par->nos)
    {
        if (n->tamSubArvore <= tamMax)
        {
            possiveis.push_back(n);
        }
    }

    if (possiveis.empty())
    {
        std::cout << "POSSIVEIS VAZIO\n";
    }

    No *escolhido2 = possiveis[Aleatorio::intAleatorio(0, possiveis.size() - 1)];

    No *copiaNovaSubarvore = copiarArvore(escolhido2);

    No *paiEscolhido = escolhido1->pai();
    if (paiEscolhido == nullptr)
    {
        delete escolhido1;
        return new Genotipo(numeroVariaveis, copiaNovaSubarvore);
    }
    copiaNovaSubarvore->setPai(paiEscolhido);

    if (paiEscolhido->getTipo() == TiposNo::BINARIA)
    {
        NoOperacaoBinaria *no = dynamic_cast<NoOperacaoBinaria *>(paiEscolhido);
        if (no->filhos()[0] == escolhido1)
        {
            no->setFilho1(copiaNovaSubarvore);
        }
        if (no->filhos()[1] == escolhido1)
        {
            no->setFilho2(copiaNovaSubarvore);
        }
    }
    else if (paiEscolhido->getTipo() == TiposNo::UNARIA)
    {
        NoOperacaoUnaria *no = dynamic_cast<NoOperacaoUnaria *>(paiEscolhido);
        if (no->filhos()[0] == escolhido1)
        {
            no->setFilho(copiaNovaSubarvore);
        }
    }

    delete escolhido1;

    No *copiaFinal = copiarArvore(copia);
    delete copia;
    return new Genotipo(numeroVariaveis, copiaFinal);
}

Genotipo *Genotipo::criarMutacao()
{
    No *mutacao = mutar();
    return new Genotipo(numeroVariaveis, mutacao);
}

No *Genotipo::mutar()
{
    No *copia = copiarArvore(raiz);
    std::vector<No *> nosCopia;
    preencherListaNos(copia, nosCopia);
    No *escolhido = nosCopia[Aleatorio::intAleatorio(0, nosCopia.size() - 1)];
    No *temp = escolhido;
    int nivel = -1;
    while (temp != nullptr)
    {
        nivel++;
        temp = temp->pai();
    }

    No *novaSubarvore = gerarArvoreAleatoria(numeroVariaveis, nivel);

    No *paiEscolhido = escolhido->pai();

    if (paiEscolhido == nullptr)
    {
        delete escolhido;
        return novaSubarvore;
    }
    else
    {
        if (paiEscolhido->getTipo() == TiposNo::BINARIA)
        {
            NoOperacaoBinaria *no = dynamic_cast<NoOperacaoBinaria *>(paiEscolhido);
            if (no->filhos()[0] == escolhido)
            {
                no->setFilho1(novaSubarvore);
            }
            if (no->filhos()[1] == escolhido)
            {
                no->setFilho2(novaSubarvore);
            }
        }
        else if (paiEscolhido->getTipo() == TiposNo::UNARIA)
        {
            NoOperacaoUnaria *no = dynamic_cast<NoOperacaoUnaria *>(paiEscolhido);
            if (no->filhos()[0] == escolhido)
            {
                no->setFilho(novaSubarvore);
            }
        }
    }

    delete escolhido;

    No *copiaFinal = copiarArvore(copia);
    delete copia;
    return copiaFinal;
}

Genotipo *Genotipo::criarCopia()
{
    No *copiaRaiz = copiarArvore(raiz);
    return new Genotipo(numeroVariaveis, copiaRaiz);
}

No *Genotipo::copiarArvore(No *noAtual)
{
    if (noAtual->getTipo() == TiposNo::BINARIA)
    {
        NoOperacaoBinaria *no = dynamic_cast<NoOperacaoBinaria *>(noAtual);
        No *f1 = copiarArvore(no->filhos()[0]);
        No *f2 = copiarArvore(no->filhos()[1]);
        No *novoNo = new NoOperacaoBinaria(no->conteudoNo(), f1, f2);
        f1->setPai(novoNo);
        f2->setPai(novoNo);
        return novoNo;
    }
    else if (noAtual->getTipo() == TiposNo::UNARIA)
    {
        NoOperacaoUnaria *no = dynamic_cast<NoOperacaoUnaria *>(noAtual);
        No *f = copiarArvore(no->filhos()[0]);
        No *novoNo = new NoOperacaoUnaria(no->conteudoNo(), f);
        f->setPai(novoNo);
        return novoNo;
    }
    else if (noAtual->getTipo() == TiposNo::CONSTANTE)
    {
        NoConstante *no = dynamic_cast<NoConstante *>(noAtual);
        return new NoConstante(no->conteudoNo());
    }
    else if (noAtual->getTipo() == TiposNo::VARIAVEL)
    {
        NoVariavel *no = dynamic_cast<NoVariavel *>(noAtual);
        return new NoVariavel(no->conteudoNo());
    }
    std::cout << "ERRO\n";
    return nullptr;
}

No *Genotipo::obterRaiz()
{
    return raiz;
}

Genotipo::~Genotipo()
{
    delete raiz;
}