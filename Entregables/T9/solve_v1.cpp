#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_set>
#define forn(i,n) for(int i=0;i<n;i++)

using namespace std;

#define MAX_WEIGHT 1000000

class Node{
    public:
        string key;
        Node(string key){
            if (key.size() != 4){
                throw invalid_argument("Key must have 4 characters");
            }
            this->key = key;
        }

        Node(){
            this->key = {'-', '-', '-', '-'};
        }

        bool operator==(const Node& n) const{
            return this->key == n.key;
        }
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
                this->weight += min(
                    abs(n1.key[i] - n2.key[i]),
                    min(
                        abs(10+n1.key[i] - n2.key[i]),
                        abs(n1.key[i] - (n2.key[i]+10))
                    )
                );
            }
        }

        Edge(){
            // Nodo vacio
            this->n1 = Node();
            this->n2 = Node();
            this->weight = MAX_WEIGHT;
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
    public:
        vector<Node> nodes;
        vector<Edge> edges;
        
        Graph(vector<string> keys){
            for(auto& key: keys){
                Node n(key);
                this->nodes.push_back(n);
            }
        }

        Graph(vector<Node> nodes, vector<Edge> edges){
            this->nodes = nodes;
            this->edges = edges;
        }

        void completeGraph(){
            unordered_set<Edge, Edge::EdgeHash, Edge::EdgeEqual> visitedEdges;
            for(int i = 0; i < this->nodes.size(); i++){
                for(int j = i+1; j < this->nodes.size(); j++){
                    Edge e = Edge(this->nodes[i], this->nodes[j]);
                    if (visitedEdges.find(e) == visitedEdges.end()) {
                        visitedEdges.insert(e);
                        this->edges.push_back(e);
                    }                    
                }
            }
        }

        Graph getAGM(){
            // Prim's Algorithm to get the AGM
            vector<Node> nodesAGM = {};
            vector<Edge> edgesAGM = {};

            int i = 0;
            int N = this->nodes.size();
            while (i < N){
                // Caso especial
                if(i == 0){
                    Edge minEdge = Edge();
                    for(Node& n: this->nodes){
                        Edge e = Edge(Node("0000"), n);
                        if(e.weight < minEdge.weight){
                            minEdge = e;
                        }
                    }
                    // cout << "min edge: " << minEdge.n1.key;
                    // cout << " " << minEdge.n2.key;
                    // cout << " " << minEdge.weight << endl;
                    edgesAGM.push_back(minEdge);
                    nodesAGM.push_back(minEdge.n2);
                    i++;
                    continue;
                }

                // Get min edge from nodesAGM to the rest of the nodes
                Edge minEdge = Edge();
                for(auto& vw: this->edges){
                    Node v = vw.n1;
                    Node w = vw.n2;
                    bool estaV = find(nodesAGM.begin(), nodesAGM.end(), v) != nodesAGM.end();
                    bool estaW = find(nodesAGM.begin(), nodesAGM.end(), w) != nodesAGM.end();
                    // cout << "v: " << v.key << " w: " << w.key << " estaV: " << estaV << " estaW: " << estaW << endl;
                    if((estaV && !estaW) || (!estaV && estaW)){
                        if(vw.weight < minEdge.weight){
                            minEdge = vw;
                        }
                    }
                }
                // add min edge to AGM
                // cout << "Min edge: " << minEdge.weight << endl;
                edgesAGM.push_back(minEdge);
                nodesAGM.push_back(minEdge.n2);
                i++;
            }
            return Graph(nodesAGM, edgesAGM);
        }

};

int solve(int N, vector<string> keys){

    Graph g = Graph(keys);       
    g.completeGraph();

    // int e=1;
    // for(Edge& vw: g.edges){
    //     cout << "e" << e << ": " << vw.n1.key << " " << vw.n2.key << " " << vw.weight << endl; 
    //     e++;
    // }

    Graph t = g.getAGM();
    int sum = 0;
    for(auto edge: t.edges){
        sum += edge.weight;
    }
    
    // cout << sum << endl;
    return sum; 
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