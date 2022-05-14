#include <iostream>
#include <vector>

#include "genotipo-arvore.h"
#include "../util/aleatorio.h"
#include "../arvore/no.h"
#include "../arvore/no-constante.h"
#include "../arvore/no-variavel.h"
#include "../arvore/no-operacao-binaria.h"
#include "../arvore/no-operacao-unaria.h"

#define NUM_OP_BIN 4
#define NUM_OP_UN 4

GenotipoArvore::GenotipoArvore(int n)
{
    numeroVariaveis = n;
    raiz = gerarArvoreAleatoria(n, 0);
    preencherListaNos(raiz);
}

No *GenotipoArvore::gerarArvoreAleatoria(int numVar, int profundidade)
{
    if (profundidade == 6)
    {
        // Gera só constante ou variavel
        int constanteOuVariavel = Aleatorio::intAleatorio(0, 1);
        if (constanteOuVariavel)
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

    int operacaoBinOperacaoUnConstanteOuVariavel = Aleatorio::intAleatorio(0, 3);
    if (operacaoBinOperacaoUnConstanteOuVariavel == 0)
    {
        No *f1 = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *f2 = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *no = new NoOperacaoBinaria(OperacaoBinaria(Aleatorio::intAleatorio(0, NUM_OP_BIN - 1)), f1, f2);
        f1->setPai(no);
        f2->setPai(no);
        return no;
    }
    if (operacaoBinOperacaoUnConstanteOuVariavel == 1)
    {
        No *f = gerarArvoreAleatoria(numVar, profundidade + 1);
        No *no = new NoOperacaoUnaria(OperacaoUnaria(Aleatorio::intAleatorio(0, NUM_OP_UN - 1)), f);
        f->setPai(no);
        return no;
    }
    if (operacaoBinOperacaoUnConstanteOuVariavel == 2)
    {
        No *no = new NoVariavel(Variavel(Aleatorio::intAleatorio(0, numVar - 1)));
        return no;
    }
    No *no = new NoConstante(Aleatorio::doubleAleatorio(-1, 1));
    return no;
}

GenotipoArvore::GenotipoArvore(int n, No *r)
{
    numeroVariaveis = n;
    raiz = r;
    preencherListaNos(r);
}

void GenotipoArvore::preencherListaNos(No *noAtual)
{
    nos.push_back(noAtual);
    for (unsigned i = 0; i < noAtual->filhos().size(); i++)
    {
        preencherListaNos(noAtual->filhos()[i]);
    }
}

void GenotipoArvore::preencherListaNos(No *noAtual, std::vector<No *> &listaNos)
{
    listaNos.push_back(noAtual);
    for (unsigned i = 0; i < noAtual->filhos().size(); i++)
    {
        preencherListaNos(noAtual->filhos()[i], listaNos);
    }
}

GenotipoArvore *GenotipoArvore::recombinar(GenotipoArvore *par)
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
        return new GenotipoArvore(numeroVariaveis, copiaNovaSubarvore);
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
    return new GenotipoArvore(numeroVariaveis, copiaFinal);
}

GenotipoArvore *GenotipoArvore::criarMutacao()
{
    No *mutacao = mutar();
    return new GenotipoArvore(numeroVariaveis, mutacao);
}

No *GenotipoArvore::mutar()
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

GenotipoArvore *GenotipoArvore::criarCopia()
{
    No *copiaRaiz = copiarArvore(raiz);
    return new GenotipoArvore(numeroVariaveis, copiaRaiz);
}

No *GenotipoArvore::copiarArvore(No *noAtual)
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

No *GenotipoArvore::obterRaiz()
{
    return raiz;
}

GenotipoArvore::~GenotipoArvore()
{
    delete raiz;
}