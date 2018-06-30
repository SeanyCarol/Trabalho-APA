#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include "Aresta.h"
#include "FuncoesAuxiliares.h"

using namespace std;

class No /// Funciona como uma lista simplesmente encadeada de arestas e como o nó de uma lista de nós
{
private:
    Aresta* primeiraAresta; /// Ponteiro para a primeira aresta do nó
    int id; /// Número de identificação do nó

    int indice; /** Índice do nó na sequência do grafo, varia obrigatoriamente de 0 até a ordem do grafo - 1. Facilita na
                criação de vetores de nós */

public:
    No* prox; /// Ponteiro para o próximo nó da lista

    No(int id, int indice);
    ~No();

    int getId();

    int getIndice();
    void sobeIndice();
    void desceIndice();

    int getGrau();

    bool insereAresta(No* sucessor, bool verificaArestaParalela = true);
    void insereArestasSubgrafo(No* n, int conj[], No* vetNos[], int tam);
};

#endif // NO_H_INCLUDED
