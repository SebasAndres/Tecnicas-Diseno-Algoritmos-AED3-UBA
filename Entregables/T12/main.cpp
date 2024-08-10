#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

long long solve(){
    
    // Lectura del input
    int n; cin >> n;     
    int D[500][500];

    unordered_set<int> S;
    int t = INT_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int q; cin >> q;
            D[i][j] = q; 
        }
    }
    vector<int> orden(n);
    for (int i=n-1; i>=0; --i) {
        int temp; cin >> temp;
        orden[i] = temp;
    }

    long long acc=0;    
    for (int k : orden) {

        // Calculo las distancias de cada {1...k-1} respecto al pivot K (ida y vuelta)
        for (int i : S) {
            for (int j : S) { // j: pivot
                D[i][k] = min(D[i][k], D[i][j] + D[j][k]); // ida 
                D[k][i] = min(D[k][i], D[k][j] + D[j][i]); // vuelta
            }
            t = min(t, D[k][i] + D[i][k]);
        }

        if (t < 0) {
            return -1; // Existe ciclo negativo
        }

        // Recalculo las distancias entre los elementos de {1..k-1} con k como pivot
        for (int i : S) {
            for (int j : S) {
                D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
                acc += D[i][j];
            }
            acc += D[i][k];
            acc += D[k][i];
        }

        // Agregamos el nodo a Gk+1        
        S.insert(k);
    }
    return acc;
}

int main() {
    int testCases; cin >> testCases;
    vector<long long> res(testCases, -1);
    for (int t = 0; t < testCases; ++t) {
        long long val = solve();
        res[t] = val;
    }
    for (int t = 0; t < testCases; ++t) 
        cout << res[t] << endl;
    return 0;
}
