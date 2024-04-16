#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#define forn(i,n) for(int i=0;i<(int)(n);i++)
using namespace std;

int solve(int numTrees, int maxHeight, int feetJump, vector<vector<int>> forestAcorns){
    /*
    Por cada altura posible me fijo el maximo posible mirando las bellotas en la altura actual de todos los arboles
    y el maximo posible que se puede obtener en la altura anterior (h-feetJump) de cualquier arbol.

    forestAcorns[tree][h] = cantidad de bellotas en el arbol `tree` en la altura `h`
    */

    int maxB[maxHeight][numTrees]; // maxB[h][tree] = max acorns at height h, tree-th tree
    forn(h, maxHeight) forn(tree, numTrees) maxB[h][tree] = 0;

    // Recorremos de abajo para arriba
    forn(h, maxHeight){

        // cout << "maxLevel " << h+1 << endl;    
        for (int tree=0; tree<numTrees; tree++){
            
            // Me fijo cuantas bellotas hay en el arbol actual en la altura h
            maxB[h][tree] = forestAcorns[tree][h]; 

            if (h-feetJump < 0){                
                if (h>0){
                    maxB[h][tree] += maxB[h-1][tree];
                }
                continue;
            }

            // Me fijo cuantas bellotas como maximo hay desde el 0 hasta h-feetJump para cualquier arbol (menos el actual)
            int maxFromAnotherTree = 0; 
            forn(t_, numTrees){
                if (t_ != tree && maxFromAnotherTree < maxB[h-feetJump][t_]){
                    maxFromAnotherTree = maxB[h-feetJump][t_];
                }
            }

            // Me fijo si conviene venir de otro arbol o estar en este
            maxB[h][tree] += max(maxB[h-1][tree], maxFromAnotherTree);

        }        
    }

    int maxCorn = 0;
    forn(tree, numTrees){
        int maxCornTree = maxB[maxHeight-1][tree];
        if (maxCornTree > maxCorn){
            maxCorn = maxCornTree;
        }
    }

    return maxCorn;
}

int main() {
    int c; 
    cin >> c;

    vector<int> res(c);

    forn(i,c){
        int t;  // number of trees >= 1
        int h;  // trees height <= 2000
        int f;  // feet desc on each jump :: 1 <= f <= 500
        cin >> t >> h >> f;

        vector<vector<int>> forestAcorns(t);

        forn(j,t){            
            int a;  // how many acorns the j-th tree has
            cin >> a;
            vector<int> acornsHeight(h+1, 0); // height of each acorn (ordered ASC)
            forn(k, a){
                int acornHeight;
                cin >> acornHeight;
                acornsHeight[acornHeight-1] += 1;
            }
            forestAcorns[j] = acornsHeight;
        }

        res[i] = solve(t, h, f, forestAcorns);
    }

    int garbage;
    cin >> garbage;

    forn(i,c){
        cout << res[i] << endl;
    }
    return 0;
}