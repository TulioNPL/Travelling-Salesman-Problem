#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <string>
using namespace std;

#define INF std::numeric_limits<int>::infinity();

typedef pair<int,int> ponto;
int matriz[100][100];   //matriz de adjacencia das cidades(com distancias)
int cidades[100];   //max 100 cidades
int dp[10000][100];
string caminho_final = "";
string fim_do_caminho = "";

vector<vector<int> > caminhos;
int n;

//Calcula a distancia entre dois pontos
int dist2pontos(ponto a, ponto b) {
    return sqrt(pow((b.first - a.first),2) + pow((b.second - a.second),2));
}

int TSPDynamic(int mask, int pos, int VISITOU_TUDO, string caminho_parcial) {
    caminho_parcial += to_string(pos+1) + ' ';

    //Se todas cidades ja foram visitadas, retorna a distancia entra a ultima cidade e a primeira
    if(mask==VISITOU_TUDO){
        fim_do_caminho = caminho_parcial;
        return matriz[pos][0];
    }

    //Se dp for diferente de -1, o valor ja foi calculado
    if(dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    
    int resp = INT_MAX;

    for(int cidade = 0; cidade < n; cidade++) {

        //Se a cidade ainda nao foi visitada, visite a cidade
        if((mask&(1<<cidade)) == 0) {
            int newResp = matriz[pos][cidade] + TSPDynamic(mask|(1<<cidade), cidade, VISITOU_TUDO,caminho_parcial);

            if(newResp < resp) {
                caminho_final = fim_do_caminho + '1';
                reverse(caminho_final.rbegin(),caminho_final.rend());
                caminho_final = caminho_final.substr(0,n*2-1);
                resp = newResp;
            }
        }
    }

    return resp;
}

int main() {
    cin >> n;
    string a;
    vector<ponto> coordenadas;
    int VISITOU_TUDO = (1<<n)-1;
    int min = INF;

    for(int i = 1; i < n; i++){
        a += to_string(i);
    }

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

    //Inicializa dp
    for(int i = 0; i <(1<<n); i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = -1;
        }
    }

    min = TSPDynamic(1,0,VISITOU_TUDO, "");
    cout << caminho_final << endl;
    cout << min << endl;

    return 0;
}