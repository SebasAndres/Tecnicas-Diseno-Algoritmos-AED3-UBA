#include <iostream>
#include <vector>
#define forn(i,n) for(int i = 0; i < n; i++)

using namespace std;

int solve(vector<int> A){
    int work = 0;
    int contador = 0;
    int N = A.size();
    for(int i=0; i<N; i++){
        contador += A[i];
        work += abs(contador);
    }
    return work;
}

int main(){
    vector<int> res;
    while (true)
    {
        int N;
        cin >> N;

        if (N == 0)
            break;

        vector<int> A(N, 0);
        forn(i,N){
            cin >> A[i];
        }
     
        res.push_back(solve(A));
    }

    forn(i,res.size()){
        cout << res[i] << endl;
    }
    return 0;
}