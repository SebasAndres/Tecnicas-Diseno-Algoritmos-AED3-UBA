#include <iostream>
#include <vector>
#include <algorithm>

#define forn(i,n) for(int i = 0; i < n; i++)
using namespace std;

/*
Observaciones: 
1. (|X|=n) -> max mex(X) = n 
2. X subset Y --> mex(X) <= mex(Y)
*/

void solve(int n, vector<int> X){
    // Counting sort : O(N)

    int k = *max_element(X.begin(), X.end());
    vector<int> M(k);
    forn(i,n){
        M[X[i]] += 1;
    }

    forn(i,k){
        if (M[i] != 0){
            int j = 0;
            while (M[i]-j != 0){
                cout << i << " ";
                j++;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;

    vector<int> X(n);
    forn(i,n)
        cin >> X[i];

    solve(n, X);
    return 0;
}