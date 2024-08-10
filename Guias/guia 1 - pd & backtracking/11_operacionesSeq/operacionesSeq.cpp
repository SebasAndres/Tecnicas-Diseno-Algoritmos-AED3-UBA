#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <tuple>

using namespace std;

bool f(
    vector<int>& v,
    int res,
    int i,
    int w,
    vector<char> &op,
    unordered_map<int, unordered_map<int,bool>> &M){

    // memoization
    if (M.count(i) && M[i].count(res)){
        return M[i][res];
    }

    // caso base
    if (i == v.size()){
        return w == res;
    }

    // poda
    if (res > w){
        return false;
    }

    // recursion
    if (f(v, res+v[i], i+1, w, op, M)) {
        op.insert(op.begin(), '+');
        M[i+1][res+v[i]] = true;
        return true;
    }
    if (f(v, res*v[i], i+1, w, op, M)) {
        op.insert(op.begin(), '*');
        M[i+1][res*v[i]] = true;
        return true;
    }
    if (v[i] != 0 && f(v, pow(res,v[i]), i+1, w, op, M)) {
        op.insert(op.begin(), '^');
        M[i+1][pow(res,v[i])] = true;
        return true;
    }

    // return     
    //     f(v, res+v[i], i+1, w) || 
    //     f(v, res*v[i], i+1, w) ||
    //     f(v, pow(res,v[i]), i+1, w);
}

void solve(vector<int> v, int w){

    // Llamar a la funcion recursiva
    unordered_map<int, unordered_map<int,bool>> M;     // (res, i) -> bool
    vector<char> op(v.size()-1);
    bool resBool = f(v, v[0], 1, w, op, M);   

    // Log respuesta
    cout << resBool << endl; 
    if (resBool){
        cout << v[0] << " ";
        for (int i = 1; i < v.size(); i++){
            cout << op[i-1];
            cout << " ";
            cout << v[i];
            cout << " ";
        }  
        cout << endl;
    }
}

int main(){
    vector<int> v = {3, 1, 5, 2, 1};
    int w = 400;

    // La complejidad temporal de este ejercicio es 
    solve(v, w);
    return 0;
}