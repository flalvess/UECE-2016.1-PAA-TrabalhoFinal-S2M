#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class Graph{
private:
	int **cost_matrix;
	int Vertices_number;

public:
	Graph(string);
	//Metodos
	float GetCost(int, int);
	int GetVerticesNumber();
	void create();

};
//--------------------------------------------------------------------------------------------------------------------------------------------
//Para Instancias das matrizes triangulares
/*
Graph::Graph(string enter) {

	ifstream arquivo;
	arquivo.open(enter.c_str(), ifstream::in);
	if (!arquivo.is_open()) {
		cout << "Arquivo não pode ser lido!";
		return;
	}
	arquivo >> Vertices_number;
	cost_matrix = new int*[Vertices_number];

	//Getting Cost Values
	int valor;
	for (int i = 0; i < Vertices_number; ++i)
	{
		cost_matrix[i] = new int[Vertices_number];

	 	for (int j = 0; j < Vertices_number; ++j)
	 	{
	 	    if(j>i)
            {
                arquivo >> valor;
                cost_matrix[i][j] = valor;
               // cost_matrix[j][i] = valor;
            }
            else
                cost_matrix[i][j] = 0;
	 	}
	}
	arquivo.close();
}*/

//--------------------------------------------------------------------------------------------------------------------------------------------
//para instancias de pontos cartesianos
Graph::Graph(string enter) {

	ifstream arquivo;
	arquivo.open(enter.c_str(), ifstream::in);
	if (!arquivo.is_open()) {
		cout << "Arquivo não pode ser lido!";
		return;
	}
	arquivo >> Vertices_number;
	cost_matrix = new int*[Vertices_number];

	int coordenadasX[Vertices_number];
	int coordenadasY[Vertices_number];
	int dx,dy;

	for(int i = 0; i<Vertices_number ; i++)
    {
        arquivo >> coordenadasX[i];
        arquivo >> coordenadasY[i];
    }

	//Getting Cost Values
	int valor;
	for (int i = 0; i < Vertices_number; ++i)
	{
		cost_matrix[i] = new int[Vertices_number];

	 	for (int j = 0; j < Vertices_number; ++j)
	 	{
	 	    dx=coordenadasX[i]-coordenadasX[j];
	 	    dy=coordenadasY[i]-coordenadasY[j];
	 	    valor = sqrt( (dx*dx) + (dy*dy) );
	 	    if(i<j)
                cost_matrix[i][j] = valor;
            else
                cost_matrix[j][i] = valor;
	 	}
	}
	arquivo.close();
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//for (int i = 0; i < Vertices_number-1; ++i)
//	 	for (int j = i+1; j <= Vertices_number; ++j)

//--------------------------------------------------------------------------------------------------------------------------------------------
//Para instancias com arestas e seus valores

/*Graph::Graph(string enter) {
    int nArestas;
    int xPon, yPon, custo;

	ifstream arquivo;
	arquivo.open(enter.c_str(), ifstream::in);
	if (!arquivo.is_open()) {
		cout << "Arquivo não pode ser lido!";
		return;
	}
	arquivo >> Vertices_number;
	arquivo >> nArestas;
	cost_matrix = new int*[Vertices_number];

	//Getting Cost Values
	int valor;
	for (int i = 0; i < Vertices_number; ++i)
	{
		cost_matrix[i] = new int[Vertices_number];

	 	for (int j = 0; j < Vertices_number; ++j)
	 	{
	 	    cost_matrix[i][j]=9999;
	 	}
	}
	for (int i = 0; i < nArestas; ++i)
	{
        arquivo >> xPon;
        arquivo >> yPon;
        arquivo >> custo;
        if(xPon<yPon)
            cost_matrix[xPon-1][yPon-1] = custo;
        else
            cost_matrix[yPon-1][xPon-1] = custo;
	}
	arquivo.close();
}*/

//--------------------------------------------------------------------------------------------------------------------------------------------
float Graph::GetCost(int i, int j) {
	return cost_matrix[i][j];
}

int Graph::GetVerticesNumber() {
	return Vertices_number;
}

#endif
