#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include "No.h"

class Grafo /// Funciona como uma lista simplesmente encadeada de nós
{
private:
    No* primeiroNo; /// Ponteiro para o primeiro nó
    int ordem; /// Ordem do grafo

public:
    Grafo();
    Grafo(istream& arq);

    ~Grafo();

    bool insereNo(int id, bool verificaRepetido = true);
    bool insereAresta(int predecessor, int sucessor);

    int getOrdem();
    int grau();

    Grafo* subGrafo(int* conj, int tam);
    void subconjuntoIndependenteMaximo(int ids[], int* tam);
};

#endif // GRAFO_H_INCLUDED
