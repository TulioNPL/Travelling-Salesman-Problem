#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <climits> 
#include <stdio.h>
#include <string.h>

using namespace std; 

#define INF INT_MAX

int N; 
int final_path[101]; //+1 porque precisa voltar ao inicial
bool visited[100]; 
int final_res = INF; 
typedef pair<int,int> ponto;
int matriz[100][100];   //matriz de adjacencia das cidades(com distancias)
int cidades[100];   //max 100 cidades

int dist2pontos(ponto a, ponto b) {
    return sqrt(pow((b.first - a.first),2) + pow((b.second - a.second),2));
}

//Encontra a menor aresta adjacente a uma cidade
int menorAresta(int adj[][100], int i) { 
    int menor = INF; 
    for (int k=0; k<N; k++) 
        if (adj[i][k]<menor && i != k) 
            menor = adj[i][k]; 
    return menor; 
} 

//encontra a segunda menor aresta adjacente a uma cidade
int segundaMenorAresta(int adj[][100], int i) { 
    int menor = INF, segMenor = INF;
   
    for (int j=0; j<N; j++) { 
        if (i != j) {
            if (adj[i][j] <= menor) { 
                segMenor = menor; 
                menor = adj[i][j]; 
            } 
            else if (adj[i][j] <= segMenor && adj[i][j] != menor) segMenor = adj[i][j];
        } 
    } 
    return segMenor; 
} 


void TSPRec(int adj[][100], int parcial, int level, int caminho_parcial[]) { 

    //Se chegar na ultima posicao e a distancia for diferente de 0
    if (level==N) { 
        if (adj[caminho_parcial[level-1]][caminho_parcial[0]] != 0) { 
            int curr_res = parcial + adj[caminho_parcial[level-1]][caminho_parcial[0]]; 

            //se a resposta parcial for menor que a final
            if (curr_res < final_res) { 
                //atualiza o melhor caminho
				for (int i=0; i<N; i++) 
        			final_path[i] = caminho_parcial[i]; 
    			final_path[N] = caminho_parcial[0]; 
                final_res = curr_res; //atualiza a melhor resposta
            } 
        } 
    } else {
        //itera pelas cidades do problema
		for (int i=0; i<N; i++) { 
            //Se a cidade nao foi visitada e se a distancia eh diferente de 0
			if (adj[caminho_parcial[level-1]][i] != 0 && visited[i] == false) { 
				parcial += adj[caminho_parcial[level-1]][i]; //atualiza a parcial
	
                //Se a parcial mais o limite atual for maior que a melhor resposta ja obtida
                //Ignora-se esse caminho e seus derivados
				if (parcial < final_res) { 
					caminho_parcial[level] = i; 
					visited[i] = true; 

					TSPRec(adj, parcial, level+1, caminho_parcial); 
				} 

				parcial -= adj[caminho_parcial[level-1]][i]; //desfaz a atualizacao da parcial
	
				memset(visited, false, sizeof(visited)); 
				for (int j=0; j<=level-1; j++) 
					visited[caminho_parcial[j]] = true; 
			} 
		} 
	}
} 
  

void TSP(int adj[][100]) { 
    int caminho_parcial[N+1];  
    memset(caminho_parcial, -1, sizeof(caminho_parcial)); 
    memset(visited, 0, sizeof(caminho_parcial)); 
 
    visited[0] = true; 
    caminho_parcial[0] = 0; 

    TSPRec(adj, 0, 1, caminho_parcial); 
} 

int main() {
    double menorDist = std::numeric_limits<double>::infinity();
    cin >> N;
    vector<ponto> coordenadas;


    //Le as coordenadas de cada cidade e adiciona no vector de coordenadas
    int x, y;
    for(int i = 0; i < N; i++) {
        cin >> x >> y;
        coordenadas.push_back(make_pair(x,y));
        cidades[i] = i;  //seta o vetor de cidades
    }

    //Calcula as distancias entre cada cidade e adiciona na matriz de adjacencia
    for(int i = 0; i< N; i++) {
        for( int j = 0; j < N; j++) {
           double distance = dist2pontos(coordenadas[i], coordenadas[j]); 
           matriz[i][j] = distance;
           matriz[j][i] = distance;
        }
    }

    TSP(matriz);

	printf("%d\n", final_res);  
    for (int i=0; i<N; i++) 
        printf("%d ", final_path[i]+1);
	cout << endl;
    return 0;
}