#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define MAX_NODES 500

class Graph {
public:
    unordered_set<int> nodes;
    int L[MAX_NODES][MAX_NODES] = {0};
     
    Graph(int nodes) {
        for(int i=0; i<nodes; i++) {
            this->nodes.insert(i);
        }
    }
};

int solve(Graph& g, vector<int>& order) {
    int (*D)[MAX_NODES][MAX_NODES];
    D = &g.L;

    // cout << endl;
    // cout << "D" << endl;
    // for(int i=0; i<g.nodes.size(); i++){
    //     for(int j=0; j<g.nodes.size(); j++){
    //         cout << (*D)[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    unordered_set<int> S;
    int t = numeric_limits<int>::max();
    reverse(order.begin(), order.end());

    int acc = 0;
    for(int k : order) {

        // Calculo las distancias de cada {1...k-1} respecto al pivot K (ida y vuelta)
        for(int i : S) {
            for(int j : S) { // j: pivot
                (*D)[i][k] = min((*D)[i][k], (*D)[i][j] + g.L[j][k]); // ida 
                (*D)[k][i] = min((*D)[k][i], (*D)[k][j] + g.L[j][i]); // vuelta
            }
            t = min(t, (*D)[k][i] + (*D)[i][k]);
        }

        if(t < 0) {
            return -1; // Existe ciclo negativo
        }

        // Recalculo las distancias entre los elementos de {1..k-1} con k como pivot
        for(int i : S) {
            for(int j : S) {
                (*D)[i][j] = min((*D)[i][j], (*D)[i][k] + (*D)[k][j]);
            }
        }

        // Agregamos el nodo a Gk+1
        S.insert(k);

        // Sumador de distancias!
        for(int i : S) {
            for(int j : S) {
                acc += (*D)[i][j];
            }
        }
    }

    return acc;
}

int main() {
    int testCases;
    cin >> testCases;
    vector<int> res(testCases, -1);
    for(int t = 0; t < testCases; ++t) {
        // Input
        int n;
        cin >> n;
        Graph g(n);        
        for(int tower = 0; tower < n; ++tower) {
            for (int i = 0; i < n; ++i) {
                int ws; cin >> ws;
                g.L[tower][i] = ws;
            }
        }

        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            cin >> order[i];
        }
        int val = solve(g, order);
        res[t] = val;
    }

    for (int t : res) {
        cout << t << endl;
    }

    return 0;
}
