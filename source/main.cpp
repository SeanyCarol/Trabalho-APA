#include <iostream>
#include <fstream>
#include <ctime>
#include "Grafo.h"

using namespace std;

int main(int argC, char* argV[])
{
    cout << endl;

    if(argC != 2)
    {
        cout << "Formato de execucao do programa:" << endl;
        cout << argV[0] << " <Arquivo de texto contendo o grafo>" << endl;
        return 1;
    }

    ifstream in(argV[1]);

    time_t start = time(NULL);
    Grafo g(in);

    int* subConj = new int[g.getOrdem()];
    int tam;

    g.subconjuntoIndependenteMaximo(subConj, &tam);
    time_t totalTime = time(NULL) - start;

    cout << "Tamanho do maior subconjunto independente encontrado: " << tam << endl;

    cout << "Elementos do subconjunto:" << endl;

    cout << "[";
    for(int i=0; i < tam; i++)
    {
        if(i > 0)
            cout << ", ";

        cout << subConj[i];
    }
    cout << "]" << endl << endl;

    cout << "Tempo gasto: ";

    if(totalTime >= 3600)
    {
        cout << totalTime / 3600 << "h ";
        totalTime = totalTime % 3600;
    }

    if(totalTime >= 60)
    {
        cout << totalTime / 60 << "min ";
        totalTime = totalTime % 60;
    }

    cout << totalTime << "seg" << endl;

    delete [] subConj;
    in.close();
    return 0;
}
