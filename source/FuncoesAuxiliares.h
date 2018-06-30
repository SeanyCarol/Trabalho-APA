#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED


/// As funções recMergeSort e mergeSort não foram implementadas no FuncoesAuxiliares.cpp por conta dos templates


/**
*   Parte recursiva do MergeSort
*
*   @params vet: Vetor a ser ordenado
*           inicio: Índice da primeira posição do vetor
*           fim: Índice da última posição do vetor
*           crescente: Se for true, será ordenado crescentemente; senão, será ordenado decrescentemente
*/
template <class Tipo>
void recMergeSort(Tipo vet[], int inicio, int fim, bool crescente)
{
    if(fim > inicio)
    {
        int ini1 = inicio;
        int ini2 = (inicio+fim)/2 + 1;
        recMergeSort(vet, ini1, (inicio+fim)/2, crescente);
        recMergeSort(vet, ini2, fim, crescente);
        Tipo* aux = new Tipo[fim-inicio + 1];

        int i;
        for(i=0; ini1 <= (inicio+fim)/2 && ini2 <= fim; i++)
        {
            if(crescente)
            {
                if(vet[ini1] < vet[ini2])
                {
                    aux[i] = vet[ini1];
                    ini1++;
                }
                else
                {
                    aux[i] = vet[ini2];
                    ini2++;
                }
            }
            else
            {
                if(vet[ini2] < vet[ini1])
                {
                    aux[i] = vet[ini1];
                    ini1++;
                }
                else
                {
                    aux[i] = vet[ini2];
                    ini2++;
                }
            }
        }

        for(; ini1 <= (inicio+fim)/2; i++)
        {
            aux[i] = vet[ini1];
            ini1++;
        }

        for(; ini2 <= fim; i++)
        {
            aux[i] = vet[ini2];
            ini2++;
        }

        for(i=0; i <= fim - inicio; i++)
            vet[i+inicio] = aux[i];

        delete [] aux;
    }
}




/**
*   Ordena um vetor de qualquer tipo seguindo o algoritmo MergeSort
*
*   @params vet: Vetor a ser ordenado
*           tam: Tamanho do vetor
*           crescente: Se for true, será ordenado crescentemente; senão, será ordenado decrescentemente
*/
template <class Tipo>
void mergeSort(Tipo vet[], int tam, bool crescente = true)
{
    recMergeSort(vet, 0, tam-1, crescente);
}




int buscaBinaria(int vet[], int tam, int n);
void incrementoBool(bool vet[], int tam);
int numTrues(bool vet[], int tam);


#endif // FUNCOESAUXILIARES_H_INCLUDED
