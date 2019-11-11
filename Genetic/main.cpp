//Codigo de github: https://github.com/marcoscastro/tsp_genetic
#include <iostream>
#include "tsp.h"
#include <math.h>
using namespace std;

typedef pair<int,int> ponto;

int n;

//Calcula a distancia entre dois pontos
int dist2pontos(ponto a, ponto b) {
    return sqrt(pow((b.first - a.first),2) + pow((b.second - a.second),2));
}

int main() {
	srand(time(NULL)); // random numbers
	
	cin >> n;
	Graph * graph1 = new Graph(n, 0);
    vector<ponto> coordenadas;

    //Le as coordenadas de cada cidade e adiciona no vector de coordenadas
    int x, y;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        coordenadas.push_back(make_pair(x,y));
    }

    //Calcula as distancias entre cada cidade e adiciona na matriz de adjacencia
    for(int i = 0; i< n; i++) {
        for( int j = 0; j < n; j++) {
           double distance = dist2pontos(coordenadas[i], coordenadas[j]); 
           graph1->addEdge(i,j,distance);
        }
    }

	Genetic genetic(graph1, 10, 1000, 5, true);

	genetic.run(); // runs the genetic algorithm

	return 0;
}
