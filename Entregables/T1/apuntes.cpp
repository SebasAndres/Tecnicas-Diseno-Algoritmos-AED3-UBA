#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <string> 
#define forn(i, n) for (int i = 0; i < n; i++)

using namespace std;

void printSolution(int numcase, vector<string> res){
    cout << "Case " << numcase << ":" << endl;
    cout << "(";
    forn(i, 4){
        cout << res[i] << ", ";
    }
    cout << res[4];
    cout << ")" << endl;
    cout << "(";
    forn(i, 4){
        cout << res[i+5] << ", ";
    }
    cout << res[9];
    cout << ")" << endl;
}

vector<tuple<string,int,int>> buildTeam(vector<tuple<string, int, int>>& players, unordered_set<int> available){
    vector<tuple<string, int, int>> res;
    forn(i, 10){
        if (available.find(i) != available.end()){
            res.insert(res.begin(), players[i]);
        }
        else {
            res.push_back(players[i]);
        }
    }
    return res;
}

tuple<int, int> computeTeamScore(vector<tuple<string, int, int>>& team){
    int attack = 0;
    int defense = 0;
    forn(i, 10){
        if (i < 5){
            attack += get<1>(team[i]);
        } 
        else {
            defense += get<2>(team[i]);
        }
    }
    return make_tuple(attack, defense);
}

void backtrack(
    vector<tuple<string, int, int>>& players,
    vector<tuple<string, int, int>>& bestTeam,
    int& maxAttack,
    int& maxDefense,
    unordered_set<int>& available,
    int maxAttackPossible){
    
    if (available.size() == 5){         
        vector<tuple<string, int, int>> tmp = buildTeam(players, available);
        tuple<int, int> team_score = computeTeamScore(tmp);
        int attack = get<0>(team_score);
        int defense = get<1>(team_score);
        if (attack > maxAttack || 
           (attack == maxAttack && defense > maxDefense) || 
           (attack == maxAttack && defense == maxDefense && get<0>(tmp[0]) < get<0>(bestTeam[0]))){
            maxAttack = attack;
            maxDefense = defense;
            bestTeam = tmp;
        }
        return;
    }

    for(auto i : available){
        unordered_set<int> available_ = available;
        available_.erase(i);

        // Poda
        if (available.size() <= 8){ 
            int actualAttack = 0;
            forn(a, 10){
                if (available.find(a) != available.end()){
                    actualAttack += get<1>(players[a]);
                }
            }
            if (actualAttack + get<1>(players[0]) + get<1>(players[1]) + get<1>(players[2]) < maxAttackPossible){
                return;
            }
        }

        backtrack(players, bestTeam, maxAttack, maxDefense, available_, maxAttackPossible);
        available_.insert(i);
    }
}

vector<string> solve(vector<tuple<string, int, int>> players){
    unordered_set<int> available = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Optimizacion
    sort(
        players.begin(),
        players.end(),
        [](const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
            return get<1>(a) > get<1>(b); 
        }
    );
    int maxAttackPossible = 0;
    forn(p, 5){
        maxAttackPossible += get<1>(players[p]);
    }

    // unordered_map<string, int> playersIndex(players.size());
    // forn(w,  10){
    //     playersIndex[get<0>(players[w])] = w;
    // }    
    // forn(i, 4){
    //     if (get<1>(players[i]) == get<1>(players[i+1])){
    //         break;
    //     }
    //     else {
    //         auto pIndex_it = playersIndex.find(get<0>(players[i]));
    //         int pIndex = pIndex_it->second;
    //         available.erase(pIndex);
    //     }
    // }

    // Aplicamos backtracking para agarrar los primeros 5
    vector<tuple<string, int, int>> bestTeam(10);
    vector<tuple<string, int, int>> tmp;
    int maxAttack = 0;
    int maxDefense = 0;

    backtrack(players, bestTeam, maxAttack, maxDefense, available, maxAttackPossible);

    // ordenamos alfabeticamente a los primeros 5 jugadores
    sort(
        bestTeam.begin(),
        bestTeam.begin() + 5,
        [](const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
            return get<0>(a) < get<0>(b);
        }
    );

    // ordenamos alfabeticamente a los ultimos 5 jugadores
    sort(
        bestTeam.begin() + 5,
        bestTeam.end(),
        [](const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
            return get<0>(a) < get<0>(b);
        }
    );

    // Formateamos las respuesta
    vector<string> res;
    forn(i, 10){
        res.push_back(get<0>(bestTeam[i]));
    }

    return res;
}

int main(){
    int TestCases;
    cin >> TestCases;

    vector<vector<string>> solutions; 

    forn(i, TestCases){
        vector<tuple<string, int, int>> players(10);        
        forn(j, 10){
            string name;
            int attack;
            int defense;
            cin >> name >> attack >> defense;
            players[j] = (make_tuple(name, attack, defense));
        }
        vector<string> res = solve(players);
        solutions.push_back(res);   
    } 

    forn(i, TestCases){
        printSolution(i+1, solutions[i]);
    }

    cout << endl;
    return 0;
}