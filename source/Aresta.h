#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

class Aresta
{
public:
    void* sucessor;  /// Ponteiro para o sucessor, void* pois nesse ponto do código o tipo No ainda não existe
    Aresta* prox;   /// Ponteiro para a próxima aresta da lista
};

#endif // ARESTA_H_INCLUDED
