#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define forn(i,n) for(int i = 0; i < n; i++)
using namespace std;

typedef int Registro;

void solve(int k, vector<Registro> R){
    /*
    Algoritmo:    
    0. Creamos un contador=0.
    1. Preprocesamos los datos para guardar por cada registro, cuales son las proximas apariciones.
    2. Heap vacio de tamaño k.
    3. Por cada registro en R:
        3.1 Si el heap no esta lleno:
            Heap.insert(registro)
        3.2 Si el heap esta lleno y el registro no esta en el heap:
            Heap.pop_head()
            contador++
            Heap.insert(registro)
    */
}