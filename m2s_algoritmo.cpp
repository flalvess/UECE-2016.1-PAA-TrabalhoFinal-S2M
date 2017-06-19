#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <list>
#include <algorithm>
#include "graph.h"
#include "listasimples.h"

#define NVIZINHOS 3364
#define NVIZINHANCAS 1000
#define INICIALIZACOES 10

using namespace std;

// Parâmetros para a Função de Park Miller
#define M 2147483647 /* 2^31 - 1 (Um número primo grande) */
#define A 16807      /* Número primo raiz de M, passa os testes estatisticos e produz um ciclo completo */
#define Q 127773     /* M / A (Para evitar overflow em A * seed) */
#define R 2836       /* M % A (Para evitar overflow em A * seed) */

// Produz uma semente aleatória
unsigned int getSeed(){
    return std::time(0) % rand()*rand();
}

// Função geradora de números aleatórios de Park Miller, ou gerador de números aleatórios Lehmer
unsigned int lcg_parkmiller() {
    unsigned int seed = getSeed();
    unsigned int hi = seed / Q;
    unsigned int lo = seed % Q;
    unsigned int test = A * lo - R * hi;
    if (test <= 0)
        test += M;
    return test;
}

// Função mapeadora de um número aleatório para um intervalo entre máximo e mínimo
unsigned int getRandomBetween(unsigned int min, unsigned int max){
    unsigned int randomNumber = lcg_parkmiller();
    
    if(max < min){
        int aux = min;
        min = max;
        max = aux;
    }
    
    return (randomNumber % (max + 1 - min)) + min;
}

// Função randômica que utiliza o gerador de números aleatórios em hardware /dev/urandom

FILE *randomFile;
unsigned int getDevUrandomValue() {
    int byte_count = 32;
    int data[byte_count];
    
    fread(&data, 1, byte_count, randomFile);
    
    unsigned long soma = 0;
    
    for (int i = 0; i < byte_count; i++) {
        soma += data[i];
    }
    
    return soma / 10;
}

void criaVetorRandom(int *vetor,int numeroVertices)
{
    tlista lista;
	for(int i = 1; i <= numeroVertices; i++)
        lista.inserir(i);

    int randDecremento = numeroVertices;

    for(int i = 0 ; i < numeroVertices;i++)
    {
        int posicaoRandom = lcg_parkmiller() % randDecremento + 1;
        int item = lista.retornarItem(posicaoRandom);
        vetor[i] = item;
        lista.removerPosicao(lista.retornarItem(posicaoRandom));

        randDecremento = randDecremento - 1;
    }
}

void imprimirMatriz(Graph graf)
{
    //Imprimindo a matriz de Distância
	for (int i = 0; i < graf.GetVerticesNumber(); ++i)
	{
		for (int j = 0; j < graf.GetVerticesNumber(); ++j)
		{
			cout << graf.GetCost(i,j) << /*"\t"*/" ";
		}
		cout << endl;
	}
}

void permutarVetorTrocaPosicaoRandom(int *vetor,int nVertices)
{
    int primeiraPosicao = 0;
    int segundaPosicao = 0;
    int aux;
    while(primeiraPosicao == segundaPosicao)
    {
        primeiraPosicao = lcg_parkmiller() % nVertices;
        segundaPosicao = lcg_parkmiller() % nVertices;
    };

    aux = vetor[primeiraPosicao];
    vetor[primeiraPosicao] = vetor[segundaPosicao];
    vetor[segundaPosicao] = aux;
}

void permutarVetorSoma(int *vetor,int nVertices)
{
    int primeiraPosicao = 0;
    int segundaPosicao = 0;
    int aux;
    while(primeiraPosicao == segundaPosicao)
    {
        primeiraPosicao = lcg_parkmiller() % nVertices;
        segundaPosicao = lcg_parkmiller() % nVertices;
    }

    if((primeiraPosicao+segundaPosicao) < (nVertices-1))
    {
        aux = vetor[primeiraPosicao];
        vetor[primeiraPosicao] = vetor[primeiraPosicao+segundaPosicao];
        vetor[primeiraPosicao+segundaPosicao] = aux;
    }
    else if(primeiraPosicao > segundaPosicao)
    {
        aux = vetor[primeiraPosicao];
        vetor[primeiraPosicao] = vetor[primeiraPosicao-segundaPosicao];
        vetor[primeiraPosicao-segundaPosicao] = aux;
    }
    else
    {
        aux = vetor[primeiraPosicao];
        vetor[primeiraPosicao] = vetor[segundaPosicao-primeiraPosicao];
        vetor[segundaPosicao-primeiraPosicao] = aux;
    }

}

void PermutaVetorIncrementa(int *vetor,int nVertices)
{
    int posicao = 0;
    int aux;
    posicao = lcg_parkmiller() % nVertices;

    if(posicao != nVertices-1)
    {
        aux = vetor[posicao+1];
        vetor[posicao+1] = vetor[posicao];
        vetor[posicao] = aux;
    }
}

int calcularMatching(int *vetor,Graph grafo)
{
    int par = 0;
    int matchingTotal = 0;
    int i = 0;
    int j = 1;
    int k = 0;
    while(k < grafo.GetVerticesNumber()/2)
    {
        if(vetor[i]<vetor[j])
        {
            par = grafo.GetCost(vetor[i]-1,vetor[j]-1);
            //cout<<endl;
            //cout<<"Valor do par "<< par<<endl;
        }
        else if(vetor[i]>vetor[j])
        {
            par = grafo.GetCost(vetor[j]-1,vetor[i]-1);
            //cout<<endl;
            //cout<<"Valor do par "<< par<<endl;
        }

        matchingTotal = matchingTotal + par;
        i = i+2;
        j = j+2;
        k = k+1;
    }
    return matchingTotal;
}

void melhorVizinhanca(int *vetor, Graph grafo, int tipo)
{
    int *melhorVetor;
    int melhor = calcularMatching(vetor,grafo);
    int atual;

    if(tipo == 0)
    {
        for(int i = 0; i < NVIZINHOS ; i++)
        {
            permutarVetorTrocaPosicaoRandom(vetor,grafo.GetVerticesNumber());
            atual = calcularMatching(vetor,grafo);
            if ( atual < melhor )
            {
                melhor = atual;
                melhorVetor = vetor;
            }
        }
    } else if(tipo == 1)
    {
        for(int i = 0; i < NVIZINHOS ; i++)
        {
            permutarVetorSoma(vetor,grafo.GetVerticesNumber());
            atual = calcularMatching(vetor,grafo);
            if ( atual < melhor )
            {
                melhor = atual;
                melhorVetor = vetor;
            }
        }
    } else if(tipo == 2)
    {
        for(int i = 0; i < NVIZINHOS ; i++)
        {
            PermutaVetorIncrementa(vetor,grafo.GetVerticesNumber());
            atual = calcularMatching(vetor,grafo);
            if ( atual < melhor )
            {
                melhor = atual;
                melhorVetor = vetor;
            }
        }
    }
}

void copiarVetor(int original[],int copiado[],int nVertices)
{
    int count;

    for(count=0 ; count < nVertices ; count++)
        copiado[count] = original[count];
}

int melhorGeracaoRandom(int matching[], Graph grafo)
{
    int nVertices = grafo.GetVerticesNumber();
    //int valorMatching = ((nVertices/2)*9999)+1;

    int melhorMatchingPermutadoRandom[nVertices];
    criaVetorRandom(melhorMatchingPermutadoRandom,nVertices);
    int valorMelhorMatchingPermutadoRandom = calcularMatching(melhorMatchingPermutadoRandom,grafo);
    int valorMatching = valorMelhorMatchingPermutadoRandom+1;

    for(int i = 0 ; i < NVIZINHANCAS ; i++)
    {
        melhorVizinhanca(melhorMatchingPermutadoRandom,grafo,0);
        valorMelhorMatchingPermutadoRandom = calcularMatching(melhorMatchingPermutadoRandom,grafo);

        if(valorMelhorMatchingPermutadoRandom < valorMatching)
        {
            valorMatching = valorMelhorMatchingPermutadoRandom;
            copiarVetor(melhorMatchingPermutadoRandom,matching,nVertices);
            cout<<"Random: "<<valorMatching<<endl;
        }
    }
    return valorMatching;
}

int melhorGeracaoSoma(int matching[], Graph grafo)
{
    int nVertices = grafo.GetVerticesNumber();
    int valorMatching = ((nVertices/2)*9999)+1;

    int melhorMatchingPermutadoSoma[nVertices];
    criaVetorRandom(melhorMatchingPermutadoSoma,nVertices);
    int valorMelhorMatchingPermutadoSoma;

    for(int i = 0 ; i < NVIZINHANCAS ; i++)
    {
        melhorVizinhanca(melhorMatchingPermutadoSoma,grafo,0);
        valorMelhorMatchingPermutadoSoma = calcularMatching(melhorMatchingPermutadoSoma,grafo);

        if(valorMelhorMatchingPermutadoSoma < valorMatching)
        {
            valorMatching = valorMelhorMatchingPermutadoSoma;
            copiarVetor(melhorMatchingPermutadoSoma,matching,nVertices);
            cout<<"Soma: "<<valorMatching<<endl;
        }
    }
    return valorMatching;
}

int melhorGeracaoIncremento(int matching[], Graph grafo)
{
    int nVertices = grafo.GetVerticesNumber();
    int valorMatching = ((nVertices/2)*9999)+1;

    int melhorMatchingPermutadoIncremento[nVertices];
    criaVetorRandom(melhorMatchingPermutadoIncremento,nVertices);
    int valorMelhorMatchingPermutadoIncremento;

    for(int i = 0 ; i < NVIZINHANCAS ; i++)
    {
        melhorVizinhanca(melhorMatchingPermutadoIncremento,grafo,0);
        valorMelhorMatchingPermutadoIncremento = calcularMatching(melhorMatchingPermutadoIncremento,grafo);

        if(valorMelhorMatchingPermutadoIncremento < valorMatching)
        {
            valorMatching = valorMelhorMatchingPermutadoIncremento;
            copiarVetor(melhorMatchingPermutadoIncremento,matching,nVertices);
            cout<<"Incremento: "<<valorMatching<<endl;
        }
    }
    return valorMatching;
}


int main(){
    srand(time(NULL));
    randomFile = fopen("/dev/urandom", "r");
    
	Graph grafo("input/Groestchel_442.txt");
    imprimirMatriz(grafo);

    int matching[grafo.GetVerticesNumber()];
    int valor = ((grafo.GetVerticesNumber()/2)*9999)+1;;
    int valor1;
    int valor2;
    int valor3;

    for(int k = 0 ; k < INICIALIZACOES ; k++)
    {
        cout<<"-----------------------------------------------------------"<<endl;
        valor1 = melhorGeracaoRandom(matching,grafo);
        valor2 = melhorGeracaoSoma(matching,grafo);
        valor3 = melhorGeracaoIncremento(matching,grafo);

        if( (valor1 <= valor2) && (valor1 <= valor3) && (valor1 <= valor))
            valor = valor1;
        if( (valor2 <= valor1) && (valor2 <= valor3) && (valor2 <= valor))
            valor = valor2;
        if( (valor3 <= valor1) && (valor1 <= valor2) && (valor1 <= valor))
            valor = valor3;

        cout<<endl;
        cout<<"Geracao: "<<k<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
    }

    //cout << "Vetor de matching que tem valor : "<< valor << endl;
    //for(int i = 0 ; i < 16 ; i++)
    //    cout << matching[i] << " ";

    //cout<<calcularMatching(matching,grafo)<<endl;

    cout << endl;
    cout<<valor<<" "<<valor1<<" "<<valor2<<" "<<valor3<<endl;
    fclose(randomFile);
    
    return 0;
}
