#include <iostream>
#include <vector>
#include <algorithm>

#define forn(i,n) for(int i = 0; i < n; i++)
using namespace std;

vector<int> solveONLgN(vector<int> X, int k){
    // Solucion en O(n lg n)
    sort(X.begin(), X.end());
    vector<int> S(k);
    for (int i = 1; i < k; i++)
        S[i] += S[i-1];
    return S;
}

vector<int> solveONLgK(vector<int> X, int k){
    // Solucion en O(n lg k)
    // Utilizamos un MinHeap con los K elementos mas grandes mientras iteramos por X
    // Si el heap tiene menos de K elementos, insertamos el elemento actual
    // Si el heap tiene K elementos, comparamos el elemento actual con el minimo del heap
    // Si el elemento actual es mayor que el minimo del heap, lo reemplazamos
    // Al final, el heap contiene los K elementos mas grandes de X
}


int main(){
    int n;
    cin >> n;

    int k;
    cin >> k;
    
    vector<int> X(n);
    forn(i,n)
        cin >> X[i];

    vector<int> S(k);
    S = solveONLgN(X, k); 

    // Log response
    forn(j,k)
        cout << S[j] << " ";

    return 0;
}