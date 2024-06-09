#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#define forn(i,n) for(int i=0;i<n;i++)

using namespace std;

#define MAX_WEIGHT 1000000

class Node{
    public:
        string key;
        Node(string key){
            if (key.size() != 4){
                throw invalid_argument("Las keys tienen 4 caracteres");
            }
            this->key = key;
        }

        Node(){
            this->key = {'-', '-', '-', '-'};
        }

        bool operator==(const Node& n) const{
            return this->key == n.key;
        }

        struct NodeHash {
            size_t operator()(const Node& n) const {
                return std::hash<std::string>()(n.key);
            }
        };

        struct NodeEqual {
            bool operator()(const Node& n1, const Node& n2) const{
                return n1.key == n2.key;
            }
        };
};

class Edge{
    public:
        Node n1;
        Node n2;
        int weight;

        Edge(Node n1, Node n2){
            this->n1 = n1;
            this->n2 = n2;
            this->weight = 0;
            for(int i = 0; i < 4; i++){
                int diff = abs(n1.key[i] - n2.key[i]); 
                this->weight += min(diff, 10-diff);
            }
        }

        Edge(){
            // Nodo vacio
            this->n1 = Node();
            this->n2 = Node();
            this->weight = MAX_WEIGHT;
        }

        bool operator==(const Edge& e) const{
            return (this->n1 == e.n1 && this->n2 == e.n2) || 
                    (this->n1 == e.n2 && this->n2 == e.n1);
        }

        struct EdgeEqual {
            bool operator()(const Edge& e1, const Edge& e2) const{
                // Modelo aristas en Grafos Simples (v,w)==(v,w)
                return (e1.n1 == e2.n1 && e1.n2 == e2.n2) || 
                        (e1.n1 == e2.n2 && e1.n2 == e2.n1);
            }
        };

        struct EdgeHash {
            size_t operator()(const Edge& e) const {
                return std::hash<std::string>()(e.n1.key + e.n2.key);
            }
        };
};

class Graph{

    private:
        pair<Node, int> nodoMasCercanoA0000(){
            // Devuelve el nodo mas cercano a 0000
            Node out_node;
            Edge minEdge = Edge();
            for(Node& node: this->nodes){
                Edge e = Edge(Node("0000"), node);
                if(e.weight < minEdge.weight){
                    minEdge = e;
                    out_node = node;
                }
            }
            return make_pair(out_node, minEdge.weight);
        }

        struct PQCompare {
            bool operator()(const pair<Node, int>& a, const pair<Node, int>& b) {
                return a.second > b.second;
            }
        };

    public:
        vector<Node> nodes;
        unordered_map<Node, std::vector<Edge>, Node::NodeHash> edges;
    
        Graph(vector<string> keys){
            for(auto& key: keys){
                Node n(key);
                this->nodes.push_back(n);
            }
        }

        void completeGraph(){
            // Genera todas las aristas del grafo completo 
            unordered_set<Edge, Edge::EdgeHash, Edge::EdgeEqual> visitedEdges;
            for(int i = 0; i < this->nodes.size(); i++){
                for(int j = i+1; j < this->nodes.size(); j++){
                    Edge e = Edge(this->nodes[i], this->nodes[j]);
                    if (visitedEdges.find(e) == visitedEdges.end()) {
                        visitedEdges.insert(e);
                        this->edges[nodes[i]].push_back(e);
                        this->edges[nodes[j]].push_back(e);
                    }                    
                }
            }
        }

        int getAGM_Length(){
            // Algoritmo de Prim modificado para obtener el largo del AGM (la suma de los pesos de sus aristas)

            unordered_set<Node, Node::NodeHash, Node::NodeEqual> visitedNodes;

            // Agarro la contrasena mas cercana a 0000
            pair<Node,int> p = nodoMasCercanoA0000();
            Node initialNode = p.first;
            int initialWeight = p.second;          

            // Armo una cola de prioridad con todas las aristas que salen de initialNode
            priority_queue<pair<Node, int>, vector<pair<Node, int>>, PQCompare> pq;
            pq.push(make_pair(initialNode, initialWeight));

            int sum = 0;    
            while(!pq.empty()){
                // Saco el nodo con menor peso
                pair<Node, int> p = pq.top();
                pq.pop();

                Node node = p.first;
                int weight = p.second;

                if (visitedNodes.find(node) != visitedNodes.end())
                    continue;
                visitedNodes.insert(node);

                sum += weight;                
                for(Edge& vw: edges[node]){
                    Node w = vw.n1 == node ? vw.n2 : vw.n1;
                    if (visitedNodes.find(w) == visitedNodes.end()){ // Para no crear ciclos
                        pq.push(make_pair(w, vw.weight));
                    }
                } 
            }

            return sum;
        }
};

int solve(int N, vector<string> keys){
    Graph g = Graph(keys);  // inicializo el grafo  
    g.completeGraph();  // agrego todas las aristas posibles

    // ver nodos
    // int n=1;
    // for(Node& node: g.nodes){
    //     cout << "n" << n << ": " << node.key << endl;
    //     n++;
    // }

    // ver aristas
    // int e=1;
    // for(Edge& vw: g.edges){
    //     cout << "e" << e << ": " << vw.n1.key << " " << vw.n2.key << " " << vw.weight << endl; 
    //     e++;
    // }

    return g.getAGM_Length(); // devuelvo el largo del AGM
}   

int main(){
    int T;
    cin >> T;
    vector<int> res;
    forn(t, T){
        int N;
        cin >> N;
        vector<string> keys(N);
        forn(c, N){
            string key;
            cin >> key;        
            keys[c] = key;
        }
        int r = solve(N, keys);
        res.push_back(r);
    }
    for(auto r: res){
        cout << r << endl;
    }
    return 0;
}