#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
using namespace std;

long long solve(vector<int> nodes, int L[500][500], vector<int>& order) {

    // Orden de destruccion inverso = orden de restauracion
    reverse(order.begin(), order.end());

    // Inicializamos D = L
    auto& D = L; 

    long long energy = 0;
    vector<int> S(order.size(), 0);

    for (int k : order) {

        // Habilito el nodo K
        S[k] = 1;

        // Actualizo todos los caminos minimos con el nodo restaurado como pivot
        for (int u : nodes) {
            for (int v : nodes)
                D[u][v] = min(D[u][v], D[u][k] + D[k][v]);
        }

        // Sumamos las distancias minimas de los nodos restaurados
        for (int u : nodes) {
            if (S[u]) {
                for (int v : nodes) {
                    if (S[u] && S[v])
                        energy += D[u][v];
                }
            }
        }
    }

    return energy;
}

int main() {
    int testCases;
    cin >> testCases;
    vector<long long> res(testCases, -1);

    for (int t = 0; t < testCases; ++t) {
        // Input
        int n;
        cin >> n;
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) {
            nodes[i] = i;
        }
        int L[500][500];
        for(int tower = 0; tower < n; ++tower) {
            for (int i = 0; i < n; ++i) {
                int w;
                cin >> w;
                L[tower][i] = w;
            }
        }
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            cin >> order[i];
        }
        int val = solve(nodes, L, order);
        res[t] = val;
    }

    for (auto t : res) 
        cout << t << endl;

    return 0;
}
