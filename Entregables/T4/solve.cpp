#include <iostream>
#include <vector>
#include <string.h>
#define forn(i,n) for(int i=0;i<(int)(n);i++)

using namespace std;

bool equivalents(string a, string b){

    // Si las cadenas son iguales, son equivalentes
    if (a==b) return true;

    // Si las cadenas son de distinta longitud, no son equivalentes
    if (a.size() != b.size()) return false;
    int n = a.size();

    // Si la longitud de las cadenas es impar, no pueden partirse en dos -> no son equivalentes
    if (n % 2 != 0) return false;

    string a1 = a.substr(0, n/2);
    string a2 = a.substr(n/2, n/2);
    string b2 = b.substr(0, n/2);
    string b1 = b.substr(n/2, n/2);

    return (equivalents(a1, b1) && equivalents(a2, b2)) || (equivalents(a1, b2) && equivalents(a2, b1));
}

int main(){
    string a,b;
    cin >> a >> b;

    bool result = equivalents(a, b);

    if (result)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;    

    return 0;
}