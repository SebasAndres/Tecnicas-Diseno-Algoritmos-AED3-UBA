#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <algorithm>
#include <string>

using namespace std;

void backtrack(
    vector<tuple<string, int, int, int>>& jugadores,
    vector<tuple<string, int, int, int>>& equipo,
    int index,
    vector<tuple<string, int, int, int>>& max_equipo,
    int& max_ataque,
    int& max_defensa,
    vector<string>& min_nombre){
 
    // Caso base
    if (equipo.size() == 5) { 

        // Calculamos el ataque con los 5 jugadores elegidos      
        int ataque_actual = 0;
        for (const auto& jugador : equipo) {
            ataque_actual += get<1>(jugador);
        }

        // Calculamos la defensa con los 5 jugadores NO elegidos
        int defensa_actual = 0;
        for (const auto& jugador : jugadores) {
            if (find(equipo.begin(), equipo.end(), jugador) == equipo.end()) {
                defensa_actual += get<2>(jugador);
            }
        }

        // Computamos el nombre de los jugadores actuales (para compararlo lexicograficamente)
        vector<string> nombre_actual;
        for (const auto& jugador : equipo) {
            nombre_actual.push_back(get<0>(jugador));
        }

        if (ataque_actual > max_ataque ||
            (ataque_actual == max_ataque && defensa_actual > max_defensa) ||
            (ataque_actual == max_ataque && defensa_actual == max_defensa && nombre_actual < min_nombre)){
            // Si es mejor que el maximo, actualizar las estructuras globales
            max_ataque = ataque_actual;
            max_defensa = defensa_actual;
            min_nombre = nombre_actual;
            max_equipo = equipo;
        }
        return;
    }
    
    if (index == jugadores.size()) {
        // No hay mas jugadores para elegir
        return;
    }

    // Agrego el i-esimo jugador
    equipo.push_back(jugadores[index]);
    // Aplico bactrack para el equipo con ese jugador, desde el proximo indice
    backtrack(jugadores, equipo, index + 1, max_equipo, max_ataque, max_defensa, min_nombre);
    // Saco el i-esimo jugador
    equipo.pop_back();
    // Aplico backtrack para el equipo sin ese jugador, desde el proximo indice
    backtrack(jugadores, equipo, index + 1, max_equipo, max_ataque, max_defensa, min_nombre);
}

void maradona() {
    int T; // Cantidad de casos de prueba
    cin >> T;

    vector<vector<string>> respuestas(T);
    
    for (int i = 0; i < T; i++) {      
        // Por cada caso, leemos los jugadores
        vector<tuple<string, int, int, int>> jugadores;
        for (int j = 0; j < 10; j++) {
            string nombre;
            int ataque, defensa;
            cin >> nombre >> ataque >> defensa;
            jugadores.push_back(make_tuple(nombre, ataque, defensa, j));
        }

        // Ordenamos los jugadores por nombre
        sort(jugadores.begin(), jugadores.end(),
            [](const tuple<string, int, int, int>& a, const tuple<string, int, int, int>& b) {
            return get<0>(a) < get<0>(b);
        });

        // Aplicamos backtrack desde el caso inicial (sin jugadores, indice 0)
        int max_ataque = 0;
        int max_defensa = 0;
        vector<string> min_nombre;
        vector<tuple<string, int, int, int>> t_delanteros;
        vector<tuple<string, int, int, int>> max_equipo;
        backtrack(jugadores, t_delanteros, 0, max_equipo, max_ataque, max_defensa, min_nombre);

        // Le agregamos al equipo con 5 jugadores delanteros, los 5 
        // jugadores defensores restantes 
        vector<string> defensores;
        for (const auto& jugador : jugadores) {
            if (find(max_equipo.begin(), max_equipo.end(), jugador) == max_equipo.end()){
                defensores.push_back(get<0>(jugador));
            }
        }        

        // Guardamos la respuesta
        vector<string> res;
        for (const auto& jugador : max_equipo) {
            res.push_back(get<0>(jugador));
        }
        for (int j = 0; j < 5; j++) {
            res.push_back(defensores[j]);
        }
        respuestas[i] = res;
    }

    for(int i=0; i<T; i++){
        vector<string> res = respuestas[i];
        cout << "Case " << i + 1 << ":" << endl;
        cout << "(";
        for (int j = 0; j < 5; j++) {
            cout << res[j];
            if (j != 4) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
        cout << "(";
        for (int j = 5; j < 10; j++) {
            cout << res[j];
            if (j != 9) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
    }
}

int main() {
    maradona();
    return 0;
}