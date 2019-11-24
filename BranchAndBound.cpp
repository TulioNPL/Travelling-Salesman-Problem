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
int caminho_final[101]; //+1 porque precisa voltar ao inicial
bool visited[100]; 
int menorDist = INF; 
typedef pair<int,int> ponto;
int matriz[100][100];   //matriz de adjacencia das cidades(com distancias)

int dist2pontos(ponto a, ponto b) {
    return sqrt(pow((b.first - a.first),2) + pow((b.second - a.second),2));
}

void branchAndBound(int parcial, int level, int caminho_parcial[]) { 

    //Se chegar na ultima posicao e a distancia for diferente de 0
    if (level==N) { 
        if (matriz[caminho_parcial[level-1]][caminho_parcial[0]] != 0) { 
            int curr_res = parcial + matriz[caminho_parcial[level-1]][caminho_parcial[0]]; 

            //se a resposta parcial for menor que a final
            if (curr_res < menorDist) { 
                //atualiza o melhor caminho
				for (int i=0; i<N; i++) 
        			caminho_final[i] = caminho_parcial[i]; 
    			caminho_final[N] = caminho_parcial[0]; 
                menorDist = curr_res; //atualiza a melhor resposta
            } 
        } 
    } else {
        //itera pelas cidades do problema
		for (int i=0; i<N; i++) { 
            //Se a cidade nao foi visitada e se a distancia eh diferente de 0
			if (matriz[caminho_parcial[level-1]][i] != 0 && visited[i] == false) { 
				parcial += matriz[caminho_parcial[level-1]][i]; //atualiza a parcial
	
                //Se a parcial for maior que a melhor resposta ja obtida
                //Ignora-se esse caminho e seus derivados
				if (parcial < menorDist) { 
					caminho_parcial[level] = i; 
					visited[i] = true; 

					branchAndBound(parcial, level+1, caminho_parcial); 
				} 

				parcial -= matriz[caminho_parcial[level-1]][i]; //desfaz a atualizacao da parcial
	
				memset(visited, false, sizeof(visited)); 
				for (int j=0; j<=level-1; j++) 
					visited[caminho_parcial[j]] = true; 
			} 
		} 
	}
} 
  

void TSP() { 
    int caminho_parcial[N+1];  
    memset(caminho_parcial, -1, sizeof(caminho_parcial)); 
    memset(visited, 0, sizeof(caminho_parcial)); 
 
    visited[0] = true; 
    caminho_parcial[0] = 0; 

    branchAndBound(0, 1, caminho_parcial); 
} 

int main() {
    cin >> N;
    vector<ponto> coordenadas;

    //Le as coordenadas de cada cidade e adiciona no vector de coordenadas
    int x, y;
    for(int i = 0; i < N; i++) {
        cin >> x >> y;
        coordenadas.push_back(make_pair(x,y));
    }

    //Calcula as distancias entre cada cidade e adiciona na matriz de adjacencia
    for(int i = 0; i< N; i++) {
        for( int j = 0; j < N; j++) {
           double distance = dist2pontos(coordenadas[i], coordenadas[j]); 
           matriz[i][j] = distance;
           matriz[j][i] = distance;
        }
    }

    TSP();

	printf("%d\n", menorDist);  
    for (int i=0; i<N; i++) 
        printf("%d ", caminho_final[i]+1);
	cout << endl;

    return 0;
}