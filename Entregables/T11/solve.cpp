#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <vector>
#include <climits>

using namespace std;

bool tieneCiclosNegativosAlcanzables(int n, unordered_map<int, vector<pair<int, int>>> &graph) {

    // Inicializamos arreglo distancias
    vector<long long> dist(n + 1, INT_MAX);
    dist[0] = 0;

    // Aplicamos Bellman-Ford, relajando cada arista
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph.size(); j++) {
            for (const auto& edge : graph[j]) {
                // Me fijo si puedo actualizar alguna arista usando a j como pivote
                int weight = edge.second; int v = edge.first;
                if (dist[j] != numeric_limits<long long>::max())
                    dist[v] = min(dist[v], dist[j] + weight);
            }
        }
    }

    // Me fijo si puedo seguir "mejorando el camino", si puedo --> hay ciclo negativo
    for (int u = 0; u < graph.size(); u++) {
        for (const auto& edge : graph[u]) {
            int w = edge.first; int weight = edge.second;
            if (dist[u] != numeric_limits<long long>::max() && dist[u] + weight < dist[w])
                return true; 
        }
    }

    return false; 
}

int main() {
    
    vector<string> out;
    while (true) {
        int n, m;
        cin >> n;
        if (n == 0)
            break;
        cin >> m;

        // Creo el grafo
        unordered_map<int, vector<pair<int,int>>> graph(n);

        for (int i = 0; i < m; ++i) {
            int s_i, n_i, k_i;
            string o_i;
            cin >> s_i >> n_i >> o_i >> k_i;
            int end_vertex = s_i + n_i;
            int weight;
            if (o_i == "lt") {
                weight = k_i - 1;
                graph[s_i-1].push_back({end_vertex, weight});
            }
            else {	
                weight = -(k_i + 1);
                graph[end_vertex].push_back({s_i-1, weight});
            }
        }

        if (tieneCiclosNegativosAlcanzables(n, graph)) 
            out.push_back("successful conspiracy");
        else 
            out.push_back("lamentable kingdom");
    }

    for (string &result : out) 
        cout << result << endl;

    return 0;
}