#include "Grafo.h"
#include "FuncoesAuxiliares.h"

using namespace std;

Grafo::Grafo()
{
    this->primeiroNo = NULL;
    this->ordem = 0;
}




/**
*   @params arq: Referência para o istream do qual serão lidas as arestas e os nós do grafo
*/
Grafo::Grafo(istream& arq)
{
    this->primeiroNo = NULL;
    this->ordem = 0;

    int predecessor, sucessor;

    while(!arq.eof())
    {
        arq >> predecessor >> sucessor;

        this->insereNo(predecessor);
        this->insereNo(sucessor);

        this->insereAresta(predecessor, sucessor);
    }
}




Grafo::~Grafo()
{
    /** Armazena o nó atual em t, anda para o próximo com p e deleta o atual, até que chegue ao fim do grafo */

    No* p = this->primeiroNo;
    No* t;
    while(p != NULL)
    {
        t = p;
        p = p->prox;
        delete t;
    }
}




/**
*   Insere no grafo um nó cujo ID é passado por parâmetro, caso não exista nenhum nó com este ID
*
*
*
*   @params id: ID do nó a ser inserido
*
*           verificaRepetido: Se for true (padrão), verifica se o nó já existe no grafo e, caso exista, não realiza a
*           inserção. Se for false, insere o nó sem verificar
*
*
*
*   @return true se o nó foi inserido com sucesso, false se já existe um nó com o mesmo ID do parâmetro
*/
bool Grafo::insereNo(int id, bool verificaRepetido)
{
    if(verificaRepetido)
    {
        for(No* p = this->primeiroNo; p != NULL; p = p->prox)
            if(p->getId() == id)
                return false;
    }

    No* novo = new No(id, this->ordem);
    novo->prox = this->primeiroNo;
    this->primeiroNo = novo;
    (this->ordem)++;

    return true;
}




/**
*   @params predecessor: ID do nó predecessor da aresta
*           sucessor: ID do nó sucessor da aresta
*
*
*
*   @return false se uma das condições é satisfeita: 1) Um dos nós informados não existe; 2) A aresta já existe;
*           3) A aresta é um self-loop
*
*           true caso a aresta foi inserida e nenhuma das 3 condições acima são verdadeiras
*/
bool Grafo::insereAresta(int predecessor, int sucessor)
{
    /** Percorre o grafo procurando pelo nó predecessor e pelo sucessor, até que chegue no final do grafo ou até que ambos
    sejam encontrados. Retorna false se pelo menos 1 deles não existe. Em seguida, insere a aresta entre eles. Caso a aresta
    não seja um self-loop, uma aresta do sucessor para o predecessor também é inserida; retorna true */

    if(predecessor == sucessor)
        return false;

    if(primeiroNo == NULL)
        return false;
    else
    {
        No* pAux = primeiroNo;
        No* pPred = NULL;
        No* pSuc = NULL;
        while(pAux != NULL && !(pPred != NULL && pSuc != NULL))
        {
            if(pAux->getId() == predecessor)
                pPred = pAux;
            if(pAux->getId() == sucessor)
                pSuc = pAux;

            pAux = pAux->prox;
        }
        if(pPred == NULL || pSuc == NULL)
            return false;
        else
        {
            if( !pPred->insereAresta(pSuc) )
                return false;

            pSuc->insereAresta(pPred);

            return true;
        }
    }
}




/**
*   @return Ordem do grafo
*/
int Grafo::getOrdem()
{
    return ordem;
}




/**
*   @return Grau de saída do grafo
*/
int Grafo::grau()
{
    /** Conta cada grau e armazena o maior deles. */

    if(primeiroNo == NULL)
        return -1;
    else
    {
        No* pAux = primeiroNo;
        int grau = -1;
        while(pAux != NULL)
        {
            int gAux = pAux->getGrau();
            if(gAux > grau)
                grau = gAux;

            pAux = pAux->prox;
        }
        return grau;
    }
}




/**
*   Aloca um subgrafo induzido por um conjunto de vértices
*
*
*
*   @params conj: Vetor com os IDs dos nós que induzirão o subgrafo. Se algum elemento do vetor não existe no grafo, será
*           considerado como um vértice isolado
*
*           tam: Tamanho do vetor
*
*
*
*   @return Ponteiro para o subgrafo induzido pelos vértices do vetor, deve ser desalocado manualmente
*/
Grafo* Grafo::subGrafo(int* conj, int tam)
{
    if(tam < 1)
    {
        Grafo* sub = new Grafo();
        return sub;
    }

    int* conjOrdenado = new int[tam];
    for(int i=0; i<tam; i++)
        conjOrdenado[i] = conj[i];

    mergeSort<int>(conjOrdenado, tam);
    No** vetNos = new No*[tam];

    for(int i=0; i<tam; i++)
    {
        vetNos[i] = new No(conjOrdenado[i], i);
        if(i == 0)
            vetNos[i]->prox = NULL;
        else
            vetNos[i]->prox = vetNos[i-1];
    }
    Grafo* sub = new Grafo();
    sub->ordem = tam;
    sub->primeiroNo = vetNos[tam-1];

    for(No* p = this->primeiroNo; p != NULL; p = p->prox)
    {
        int indice = buscaBinaria(conjOrdenado, tam, p->getId());
        if(indice != -1)
            p->insereArestasSubgrafo(vetNos[indice], conjOrdenado, vetNos, tam);
    }

    delete [] conjOrdenado;
    delete [] vetNos;

    return sub;
}




/**
*   Executa um algoritmo força bruta para obter o maior subconjunto independente possível no grafo
*
*
*
*   @params idsMaiorSubconjunto: Vetor de inteiros no qual será armazenado o subconjunto. Deve possuir pelo menos n
*                                posições disponíveis
*
*           tamMaiorSubconjunto: Ponteiro para o inteiro no qual será armazenado o número de elementos do subconjunto
*/
void Grafo::subconjuntoIndependenteMaximo(int idsMaiorSubconjunto[], int* tamMaiorSubconjunto)
{
    bool* combinacao = new bool[this->ordem];
    for(int i=0; i < this->ordem; i++)
        combinacao[i] = false;

    No** vetNos = new No*[this->ordem];
    for(No* p = this->primeiroNo; p != NULL; p = p->prox)
    {
        vetNos[p->getIndice()] = p;
    }

    incrementoBool(combinacao, this->ordem); /// O subconjunto deve ter pelo menos 1 elemento

    int* idsSubconjuntoAtual = new int[this->ordem];
    int tamSubconjuntoAtual = numTrues(combinacao, this->ordem);
    *tamMaiorSubconjunto = 0;

    while(tamSubconjuntoAtual != 0)
    {
        if(tamSubconjuntoAtual > *tamMaiorSubconjunto)
        {
            int j = 0;
            for(int i=0; i < this->ordem; i++)
            {
                if(combinacao[i])
                {
                    idsSubconjuntoAtual[j] = vetNos[i]->getId();
                    j++;
                }
            }

            Grafo* subgrafoInduzidoSubconjunto = this->subGrafo(idsSubconjuntoAtual, tamSubconjuntoAtual);

            if(subgrafoInduzidoSubconjunto->grau() == 0)
            {
                *tamMaiorSubconjunto = tamSubconjuntoAtual;

                for(int i=0; i < *tamMaiorSubconjunto; i++)
                    idsMaiorSubconjunto[i] = idsSubconjuntoAtual[i];
            }

            delete subgrafoInduzidoSubconjunto;
        }

        incrementoBool(combinacao, this->ordem);
        tamSubconjuntoAtual = numTrues(combinacao, this->ordem);
    }

    delete [] combinacao;
    delete [] idsSubconjuntoAtual;
    delete [] vetNos;
}
