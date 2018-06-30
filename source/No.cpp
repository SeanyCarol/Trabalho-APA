#include <iostream>
#include "No.h"




/**
*   @params id: ID do novo nó
*           indice: Índice do novo nó no grafo
*/
No::No(int id, int indice)
{
    this->primeiraAresta = NULL;
    this->id = id;
    this->indice = indice;
}




No::~No()
{
    /** Armazena a aresta atual em t, anda para a próxima com p e deleta a atual, até que chegue ao fim do nó */

    Aresta* p = this->primeiraAresta;
    Aresta* t;
    while(p != NULL)
    {
        t = p;
        p = p->prox;
        delete t;
    }
}




/**
*   @return ID do nó
*/
int No::getId()
{
    return this->id;
}




/**
*   @return Índice do nó no grafo
*/
int No::getIndice()
{
    return this->indice;
}



/**
*   Aumenta em 1 unidade o índice do nó
*/
void No::sobeIndice()
{
    (this->indice)++;
}



/**
*   Diminui em 1 unidade o índice do nó
*/
void No::desceIndice()
{
    (this->indice)--;
}




/**
*   @return Grau do nó
*/
int No::getGrau()
{
    /// Conta e retorna o número de arestas que saem do nó

    int cont = 0;
    for(Aresta* p = this->primeiraAresta; p != NULL; p = p->prox)
        cont++;

    return cont;
}




/**
*   Insere uma nova aresta no nó
*
*
*
*   @params sucessor: Ponteiro para o nó sucessor
*
*           verificaArestaParalela: Se for true (padrão), verificará se a aresta já existia antes, se sim, não a insere. Se
*           for false, insere a aresta sem verificar
*
*
*
*   @return true se não existia aresta para o sucessor e uma nova foi inserida, false caso contrário
*/
bool No::insereAresta(No* sucessor, bool verificaArestaParalela)
{
    if(verificaArestaParalela)
    {
        for(Aresta* p = this->primeiraAresta; p != NULL; p = p->prox)
            if( (No*)(p->sucessor) == sucessor )
                return false;
    }

    Aresta* nova = new Aresta;
    nova->sucessor = (void*)sucessor;
    nova->prox = this->primeiraAresta;
    this->primeiraAresta = nova;

    return true;
}




/**
*   Insere em n cada aresta do nó cujo sucessor está contido em conj
*
*   @params n: Ponteiro para o nó cujas arestas serão inseridas
*           conj: Vetor ordenado com os IDs dos nós que formam o subgrafo
*           vetNos: Vetor com os ponteiros dos nós do subgrafo
*           tam: Ordem do subgrafo
*/
void No::insereArestasSubgrafo(No* n, int conj[], No* vetNos[], int tam)
{
    for(Aresta* p = this->primeiraAresta; p != NULL; p = p->prox)
    {
        int i = buscaBinaria(conj, tam, ( (No*)(p->sucessor) )->getId() );
        if(i != -1)
            n->insereAresta(vetNos[i], false);
    }
}
