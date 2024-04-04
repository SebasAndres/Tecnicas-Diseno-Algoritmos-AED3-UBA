/* MURCIA SKYLINE:
-- Observacion CLAVE: 
    NO IMPORTA QUE LOS EDIFICIOS SEAN CONSECUTIVOS O NO PARA CONTAR LA LONGITUD
    DE LAS SUBSECUENCIAS CRECIENTES Y DECRECIENTES QUE TERMINAN EN LA I-ESIMA POSICION.
*/
#include <iostream>
#include <vector>
#define forn(i, n) for(int i = 0; i < n; i++)
using namespace std;

void solve(int numCase, int n, int heights[], int widths[]){
    // Solucion de cada caso particular

    // Guardan la longitud de la maxima secuencia creciente y decreciente
    int maxIncreasingSequence = 0;
    int maxDecreasingSequence = 0;

    // Guardan la longitud de la maxima secuencia creciente y decreciente 
    // que termina en el elemento i
    vector<int> inS(n);
    vector<int> deS(n);

    forn(i, n){

        // Inicializo las secuencias en el elemento i
        inS[i] = widths[i];
        deS[i] = widths[i];

        forn(j, i){            

            // Si el elemento j es menor que el elemento i, entonces
            if (heights[j] < heights[i]){
                /*
                Si la altura del edificio j es menor que la altura del edificio i,
                entonces el edificio i tiene una subsecuencia creciente atras
                que en la que pertenece el edificio j. 
                
                En este caso, actualizamos la longitud de la subsecuencia 
                creciente más larga que termina en el edificio i (inS[i]):

                insS[i] = máx(
                    valor actual,
                    la longitud de la subsecuencia creciente más larga
                    que termina en el edificio j más la anchura del 
                    edificio i
                )
                */               
                inS[i] = max(inS[i], inS[j] + widths[i]);
            }

            // Si el elemento j es mayor que el elemento i, entonces
            if (heights[j] > heights[i]){
                deS[i] = max(deS[i], deS[j] + widths[i]);
            }
        }

        // Actualizo los maximos de todo el caso
        maxIncreasingSequence = max(maxIncreasingSequence, inS[i]);
        maxDecreasingSequence = max(maxDecreasingSequence, deS[i]);
    }

    // Imprimo la solucion
    if(maxDecreasingSequence <= maxIncreasingSequence)
        cout << "Case " << numCase << ". Increasing (" << maxIncreasingSequence << "). Decreasing (" << maxDecreasingSequence << ").\n";
    else
        cout << "Case " << numCase << ". Decreasing (" << maxDecreasingSequence << "). Increasing (" << maxIncreasingSequence << ").\n";
}

int main(){
    int NUM_CASES;
    cin >> NUM_CASES;
    forn(i, NUM_CASES){
        int n;
        cin >> n;
        int heights[n];
        int widths[n];
        forn(i, n){
            cin >> heights[i];
        }
        forn(i, n){
            cin >> widths[i];
        }
        solve(i+1, n, heights, widths);
    }
    return 0;
}