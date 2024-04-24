#include <iostream>
#include <vector>
#include <string.h>
#define forn(i,n) for(int i=0;i<(int)(n);i++)

using namespace std;

bool equivalentes(string a, string b){

    // Si las cadenas son iguales, son equivalentes
    if (a==b) return true;

    // Si las cadenas son de distinta longitud, no son equivalentes
    if (a.size() != b.size()) return false;
    int n = a.size();

    // Si la longitud de las cadenas es impar, no pueden partirse en dos -> no son equivalentes
    if (n % 2 != 0) return false;

    // Divido en las mitades
    string a1 = a.substr(0, n/2);
    string a2 = a.substr(n/2, n/2);
    string b2 = b.substr(0, n/2);
    string b1 = b.substr(n/2, n/2);

    return (equivalentes(a1, b1) && equivalentes(a2, b2)) || (equivalentes(a1, b2) && equivalentes(a2, b1));
}

int main(){
    string a;
    string b;
    cin >> a >> b;

    if (equivalentes(a, b))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;    

    return 0;
}