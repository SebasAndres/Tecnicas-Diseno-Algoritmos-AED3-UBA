#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
public:
    int nodes;
    unordered_map<int, unordered_map<int, int>> L;

    Graph(int n) : nodes(n) {
        for (int i = 0; i < n; ++i) {
            L[i] = {};
        }
    }
};

int solve(Graph& g, vector<int>& order) {
    /*
    Calculamos las distancias con el algoritmo de Dantzig, agregando los nodos a 
    Gk en el orden inverso que son destruidas las torres.
    */

    auto& D = g.L;
    auto& L = g.L;
    unordered_set<int> S;
    int t = INT_MAX;
    reverse(order.begin(), order.end());

    int acc = 0;
    for (int k : order) {

        // Calculo las distancias de cada {1...k-1} respecto al pivot K (ida y vuelta)
        for (int i : S) {
            for (int j : S) { // j: pivot
                D[i][k] = min(D[i][k], D[i][j] + L[j][k]); // ida 
                D[k][i] = min(D[k][i], D[k][j] + L[j][i]); // vuelta
                t = min(t, D[k][i] + D[i][k]);
            }
        }

        if (t < 0) {
            return -1; // Existe ciclo negativo
        }

        // Recalculo las distancias entre los elementos de {1..k-1} con k como pivot
        for (int i : S) {
            for (int j : S) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }

        // Agregamos el nodo a Gk+1        
        S.insert(k);

        // Sumador de distancias!
        for (int i : S) {
            for (int j : S) {
                acc += D[i][j];
            }
        }
    }

    return acc;
}

int main() {
    int testCases;
    cin >> testCases;

    vector<int> res(testCases, -1);
    for (int t = 0; t < testCases; ++t) {
        // Input
        int n;
        cin >> n;
        Graph g(n);
        for (int tower = 0; tower < n; ++tower) {
            vector<int> ws(n);
            for (int i = 0; i < n; ++i) {
                cin >> ws[i];
                g.L[tower][i] = ws[i];
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
