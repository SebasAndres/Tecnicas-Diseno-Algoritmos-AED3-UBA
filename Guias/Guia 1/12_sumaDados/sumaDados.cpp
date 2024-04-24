#include <iostream>
#include <vector>
#include <cmath>

#define forn(i,n) for(int i = 0; i < n; i++)

using namespace std;

int f(
    int n,
    int s,
    int k,
    vector<vector<int>> &M){

    if (M[n][s] != -1)
        return M[n][s];

    if (n == 1){
        int r;
        if (s<=k)
            r=1;
        r=0;
        M[n][s] = r;
    }

    int r = 0;
    forn(i, k){
        r += f(n-1, s-i, k, M);
    }

    M[n][s] = r;
    return r;
}

int g(
    int n,
    int s,
    int k,
    vector<vector<int>> &Mg){

    if (Mg[n][s] != -1)
        return Mg[n][s];

    if (n == 1){
        int r;
        if (s<=k)
            r=1;
        r=0;
        Mg[n][s] = r;
    }

    int r = 0;
    forn(i, k){
        r += g(n-1, s-i, i, Mg);
    }

    Mg[n][s] = r;
    return r;
}


void solve(int n, int s, int k){
    vector<vector<int>> Mf(n+1, vector<int>(s+1, -1));
    vector<vector<int>> Mg(n+1, vector<int>(s+1, -1));
    cout << f(n, s, k, Mf) << endl;
    cout << g(n, s, k, Mg) << endl;
}

int main(){
    int n, s, k;
    cin >> n >> s >> k;
    solve(n, s, k);
    return -1;
}