#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
using namespace std;

typedef pair<int,int> ponto;
int matriz[100][100];   //matriz de adjacencia das cidades(com distancias)
int cidades[100];   //max 100 cidades
vector<vector<int> > caminhos;
int n;

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

//Encontra as possiveis permutacoes
void findPermutations(int a[], int n) { 
    do { 
        vector<int> c;
        for (int i = 0; i < n; i++) { 
            c.push_back(a[i]);
        }
        c.push_back(a[0]);
        caminhos.push_back(c); 
    } while (next_permutation(a+1, a+n)); 
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

    findPermutations(cidades,n);

    int pos;
    for(int i = 0; i < caminhos.size(); i++) {
        double dist = calcDist(caminhos[i]);
        if( dist < menorDist) {
            menorDist = dist;
            pos = i;
        }
    }

    //Printa a resposta
    cout << menorDist << endl;
    for(int i = 0; i < caminhos[pos].size()-1; i++) {
        cout << caminhos[pos][i]+1 << ' ';
    }
    cout << endl;
    return 0;
}
