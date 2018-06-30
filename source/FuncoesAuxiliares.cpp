#include <cstdlib>
#include "FuncoesAuxiliares.h"

/**
*
*   @params vet: Vetor ordenado crescentemente
*           tam: Tamanho do vetor
*           n : Elemento a ser encontrado no vetor
*
*   @return Posição do elemento n no vetor caso exista, -1 caso contrário
*/
int buscaBinaria(int vet[], int tam, int n)
{
    int inicio = 0, fim = tam-1;
    while(fim >= inicio)
    {
        if(n == vet[(fim+inicio)/2])
            return (fim+inicio)/2;
        else if(n < vet[(fim+inicio)/2])
            fim = (fim+inicio)/2 - 1;
        else
            inicio = (fim+inicio)/2 + 1;
    }

    return -1;
}




/**
*   Tratando um vetor de booleanos como um número em binário, soma 1 unidade ao número
*
*   @params vet: Vetor de booleanos
*           tam: Tamanho do vetor
*/
void incrementoBool(bool vet[], int tam)
{
    for(int i = tam - 1; i >= 0; i--)
    {
        vet[i] = !vet[i];
        if(vet[i])
            break;
    }
}




/**
*   @params vet: Vetor de booleanos
*           tam: Tamanho do vetor
*
*   @return Número de posições do vetor com valor true
*/
int numTrues(bool vet[], int tam)
{
    int num = 0;

    for(int i=0; i < tam; i++)
    {
        if(vet[i])
            num++;
    }

    return num;
}
