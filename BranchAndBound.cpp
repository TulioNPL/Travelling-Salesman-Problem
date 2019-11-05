#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <bits/stdc++.h>

using namespace std;

#define INF std::numeric_limits<double>::infinity();

typedef pair<int,int> ponto;
int matriz[100][100];   //matriz de adjacencia das cidades(com distancias)
int cidades[100];   //max 100 cidades
int n;
double melhorDist = INF;
int melhorCaminho[100];

double calcDist(vector<int> caminho) {
	double dist = 0;
	for(int i = 1; i < caminho.size(); i++) {
		dist += matriz[caminho[i-1]][caminho[i]];
	}
	return dist;
}

//Calcula a distancia entre dois pontos
int dist2pontos(ponto a, ponto b) {
	return sqrt(pow((b.first - a.first),2) + pow((b.second - a.second),2));
}

void branchAndBound(int a[], int l, int r, double parcial) {
	parcial += matriz[a[l-1]][a[l]];
	if (l == r) {
		double dist_final = matriz[a[l]][a[0]] + parcial;	
		 
		if(dist_final < melhorDist) {
			melhorDist = dist_final;
			for(int i = 0; i < n; i++) {
				melhorCaminho[i] = a[i];
			}
		}
	} else {
		for (int i = l; i <= r; i++) {
			swap(a[l], a[i]);
			if(parcial < melhorDist) branchAndBound(a, l+1, r, parcial);
			//backtrack
			swap(a[l], a[i]);
		}
	}
}

int main() {
	double menorDist = std::numeric_limits<double>::infinity();
	cin >> n;
	vector<ponto> coordenadas;

	//Le as coordenadas de cada cidade e adiciona no vector de coordenadas
	int x, y;
	for(int i = 0; i < n; i++) {
		cin >> x >> y;
		coordenadas.push_back(make_pair(x,y));
		cidades[i] = i;  //seta o vetor de cidades
	}

	//Calcula as distancias entre cada cidade e adiciona na matriz de adjacencia
	for(int i = 0; i< n; i++) {
		for( int j = 0; j < n; j++) {
			double distance = dist2pontos(coordenadas[i], coordenadas[j]);
			matriz[i][j] = distance;
			matriz[j][i] = distance;
		}
	}

	branchAndBound(cidades,1,n-1, 0);

	printf("%2.f\n", melhorDist);
	for(int i = 0; i < n; i++){
		cout << melhorCaminho[i] << ' ';
	}
	cout << endl;

	return 0;
}
