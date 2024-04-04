#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < n; i++)
using namespace std;

// Imprime la solucion en pantalla
void printSolution(unordered_map<string, tuple<int, int, int>> team){
    vector<string> delanteros(5);
    vector<string> defensores(5);
    for (const auto& pair : team) {
        tuple<int, int, int> player = pair.second;
        int index = get<0>(player);
        if (index < 5)
            delanteros[index] = pair.first;
        else
            defensores[index-5] = pair.first;
    }   
    // Ordenamos alfabeticamente
    sort(delanteros.begin(), delanteros.end());
    sort(defensores.begin(), defensores.end());
    // Delanteros
    cout << "(";
    forn(i, 4){
        cout << delanteros[i] << ", ";
    }
    cout << delanteros[4];
    cout << ")" << endl;
    // Defensores
    cout << "(";
    forn(q, 4){
        cout << defensores[q] << ", ";
    }
    cout << defensores[4];
    cout << ")" << endl;
}

// Devuelve el puntaje de ataque y defensa de un equipo
tuple<int, int> getScore(unordered_map<string, tuple<int, int, int>> team){
    int attack_score = 0;
    int defense_score = 0;
    for (const auto& pair : team) {
        tuple<int, int, int> player = pair.second;
        int index = get<0>(player);    
        if (index < 5)
            attack_score += get<1>(player);
        else
            defense_score += get<2>(player);
    }
    return make_tuple(attack_score, defense_score);
}   

// Devuelve el mejor posible ataque
int getBestPossibileAttack(vector<tuple<string, int, int>> case_players){
    vector<tuple<string, int, int>> top_attackers = case_players;
    sort(top_attackers.begin(), top_attackers.end(), [](tuple<string, int, int> a, tuple<string, int, int> b){
        return get<1>(a) > get<1>(b);
    });
    int best_possible_attack = 0;
    forn(i, 5){
        best_possible_attack += get<1>(top_attackers[i]);
    }
    return best_possible_attack;
}

// Funcion para saber si podemos extender la solucion parcial a una solucion final
bool couldExtendToSolution(int best_possible_attack, unordered_map<string, tuple<int, int, int>> team){
    tuple<int,int> team_score = getScore(team);
    int attack_score = get<0>(team_score);
    return attack_score >= best_possible_attack;
}

// Devuelve los primeros 5 jugadores con mas ataque sin incluir los que empatan al final
unordered_map<string, tuple<int, int, int>> getFirstPlayers(vector<tuple<string, int, int>> case_players){
    unordered_map<string, tuple<int, int, int>> res = {};
    vector<tuple<string, int, int>> top_attackers = case_players;
    sort(top_attackers.begin(), top_attackers.end(), [](tuple<string, int, int> a, tuple<string, int, int> b){
        return get<1>(a) > get<1>(b);
    });
    int i = 0;
    while (i<6){
        if (get<1>(top_attackers[i]) != get<1>(top_attackers[i+1])){
            res[get<0>(top_attackers[i])] = make_tuple(i, get<1>(top_attackers[i]), get<2>(top_attackers[i]));
        }
        else {
            int repetidosConsecutivos = 0;
            while (get<1>(top_attackers[i]) == get<1>(top_attackers[i+repetidosConsecutivos])){
                repetidosConsecutivos++;
            }
            if (i+repetidosConsecutivos < 5){
                forn(j, repetidosConsecutivos){
                    res[get<0>(top_attackers[i+j])] = make_tuple(i+j, get<1>(top_attackers[i+j]), get<2>(top_attackers[i+j]));
                }    
            }
            break;
        }
        i++;   
    }
    return res;
}

// Backtracking para encontrar el mejor equipo
void solve(vector<tuple<string, int, int>> case_players,
           unordered_map<string, tuple<int, int, int>> curr,
           int& best_att_score_case,
           int& best_def_score_case, 
           unordered_map<string, tuple<int, int, int>>& best_team_case,
           int best_possible_attack){

    unordered_map<string, tuple<int, int, int>> res = curr;

    // Caso base :: hay 10 jugadores
    if (res.size() == 5){
        // Agrego los otros 5 jugadores restantes
        for(auto player : case_players){
            string p_name = get<0>(player);
            if (res.find(p_name) == res.end()){
                res[p_name] = make_tuple(res.size(), get<1>(player), get<2>(player));
            }
        }
        
        // Calculo el puntaje del equipo
        tuple<int,int> team_score = getScore(res);
        int attack_score = get<0>(team_score);
        int defense_score = get<1>(team_score);

        // Reglas de decision
        if (attack_score > best_att_score_case){
            best_att_score_case = attack_score;
            best_def_score_case = defense_score;            
            best_team_case = res;
        }
        else if (attack_score == best_att_score_case){
            if (defense_score > best_def_score_case){
                best_def_score_case = defense_score;
                best_team_case = res;
            }
            else if (defense_score == best_def_score_case){
                // Elegir atacantes que vienen antes lexicograficamente
                // Comparar RES con BEST_TEAM_CASE y elegir
            }
        }

        return;
    }

    // Caso recursivo
    for(auto player : case_players){
        
        // Decodificamos los datos del jugador
        string p_name = get<0>(player);
        int p_attack_skill = get<1>(player);
        int p_defense_skill = get<2>(player);
    
        // Valido si el jugador no está en el equipo
        if (res.find(p_name) == res.end()){

            // Agrego el jugador al equipo
            res[p_name] = make_tuple(res.size(), p_attack_skill, p_defense_skill);

            // Completo el resto de jugadores si es se puede extender a una solucion valida
            if (res.size()<5 || couldExtendToSolution(best_possible_attack, res)){
                solve(
                    case_players,
                    res,
                    best_att_score_case,
                    best_def_score_case,
                    best_team_case,
                    best_possible_attack);
            }
            
            // Elimino el jugador del equipo
            res.erase(p_name);
        }
    }
}

int main() {
    // INPUT
    int T; // Número de casos de prueba
    cin >> T;
    // Lectura de jugadores por cada caso de prueba
    vector<vector<tuple<string, int, int>>> cases(T);
    forn(i, T){
        // Por cada caso leo y agrego los 10 jugadores
        forn(p, 10){
            string name;
            int attack_skill;
            int defense_skill;
            cin >> name >> attack_skill >> defense_skill;
            tuple<string, int, int> player(name, attack_skill, defense_skill); 
            cases[i].push_back(player);            
        }          
    }

    // INPUT HARCODEADO
    // int T = 2;    
    // std::vector<std::vector<std::tuple<std::string, int, int>>> cases = {
    //     {
    //         std::make_tuple("sameezahur", 20, 21),
    //         std::make_tuple("sohelh", 18, 9),
    //         std::make_tuple("jaan", 17, 86),
    //         std::make_tuple("sidky", 16, 36),
    //         std::make_tuple("shamim", 16, 18),
    //         std::make_tuple("shadowcoder", 12, 9),
    //         std::make_tuple("muntasir", 13, 4),
    //         std::make_tuple("brokenarrow", 16, 16),
    //         std::make_tuple("emotionalblind", 16, 12),
    //         std::make_tuple("tanaeem", 20, 97)
    //     },
    //     {
    //         std::make_tuple("sameezahur", 20, 21),
    //         std::make_tuple("sohelh", 18, 9),
    //         std::make_tuple("jaan", 17, 86),
    //         std::make_tuple("sidky", 16, 36),
    //         std::make_tuple("shamim", 16, 18),
    //         std::make_tuple("shadowcoder", 12, 9),
    //         std::make_tuple("muntasir", 13, 4),
    //         std::make_tuple("brokenarrow", 16, 16),
    //         std::make_tuple("emotionalblind", 16, 12),
    //         std::make_tuple("tanaeem", 20, 97)
    //     }
    // };

    // OUTPUT :: Procesamiento de los casos
    forn(i, T){
        cout << "Case " << i+1 << ":" << endl;
        
        unordered_map<string, tuple<int, int, int>> best_team_case = {};
        int best_possible_attack = getBestPossibileAttack(cases[i]);
        int best_att_score_case = 0;  
        int best_def_score_case = 0;  

        // Agarramos los primeros elementos con mas ataque, sin incluir aquellos que tienen empate,
        // ademas como mucho traemos 5
        unordered_map<string, tuple<int, int, int>> tmp = getFirstPlayers(cases[i]);

        // Resolver el caso
        solve(
            cases[i],
            tmp,
            best_att_score_case,
            best_def_score_case,
            best_team_case,
            best_possible_attack);

        // Imprimir el equipo
        printSolution(best_team_case);
    }

    return 0;
}

