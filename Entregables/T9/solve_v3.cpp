#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
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
    public:
        vector<Node> nodes;
        vector<Edge> edges;
        
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
                        this->edges.push_back(e);
                    }                    
                }
            }
        }

        int getAGM_Length(){
            // Algoritmo de Prim modificado para obtener el largo del AGM (la suma de los pesos de sus aristas)
            
            int sum = 0; // Suma de los pesos de las aristas del AGM [OUT]
            int i = 0; // Numero de nodos en el AGM
            int N = this->nodes.size(); // Numero de nodos en el grafo original

            // Nodos y aristas del AGM
            // Uso una estructura de datos que me permite buscar nodos y aristas en O(1)
            unordered_set<Node, Node::NodeHash, Node::NodeEqual> nodesAGM;
            unordered_set<Edge, Edge::EdgeHash, Edge::EdgeEqual> edgesAGM;
            
            // CASO INICIAL (primer arista del AGM, desde 0000)
            // Agarro la arista de menor peso que tenga a 0000 como uno de sus extremos
            Edge minEdge = Edge();
            bool is0000 = false;
            for(Node& n: this->nodes){
                if (n.key == "0000"){
                    is0000 = true;
                    continue;
                } 
                Edge e = Edge(Node("0000"), n);
                if(e.weight < minEdge.weight)
                    minEdge = e;
            }
            // Si 0000 esta en el grafo original, la agrego al AGM como primer nodo
            if (is0000){
                nodesAGM.insert(Node("0000"));
                i++;
            } 
            // Agregamos la arista y el "segundo" vertice (es el 1ro si 0000 no esta en el grafo)
            edgesAGM.insert(minEdge);
            nodesAGM.insert(minEdge.n2);
            sum += minEdge.weight;
            i++;

            // CASO GENERAL
            // Uso una estructura de datos que me permite ver que aristas estan disponibles por nodo en O(1)
            // La idea es ver solo aristas que tengan un nodo en el AGM, por lo que armo en O(M) una estructura
            // que me permita ver en O(1) las aristas disponibles para cada nodo (un dicc)
            unordered_set<Edge, Edge::EdgeHash, Edge::EdgeEqual> visitedEdges;
            unordered_map<Node, vector<Edge>, Node::NodeHash, Node::NodeEqual> availableEdges;
            for(Edge& vw: this->edges){
                Node v = vw.n1;
                Node w = vw.n2;
                
                // Agrego para V
                if(availableEdges.find(v) != availableEdges.end()){
                    availableEdges[v].push_back(vw);
                } 
                else {
                    availableEdges[v] = vector<Edge>();
                    availableEdges[v].push_back(vw);
                }

                // Agrego para W
                if(availableEdges.find(w) != availableEdges.end()){
                    availableEdges[w].push_back(vw);
                } 
                else {
                    availableEdges[w] = vector<Edge>();
                    availableEdges[w].push_back(vw);
                }
            }

            // Mientras no haya visitado todos los nodos
            while (i < N){
                // Busco la arista de menor peso que tenga un nodo en el AGM y otro que no
                Edge minEdge = Edge();
                bool isV_InMin = false; // True iff node1 in minEdge
                for(Node nn: nodesAGM){
                    for(auto& vw: availableEdges[nn]){
                        // Si la arista ya fue visitada, la salteo
                        if(visitedEdges.find(vw) != visitedEdges.end())
                            continue;
                        // Valido si la arista tiene un nodo en el AGM y otro que no
                        Node v = vw.n1; 
                        Node w = vw.n2;
                        bool estaV = find(nodesAGM.begin(), nodesAGM.end(), v) != nodesAGM.end();
                        bool estaW = find(nodesAGM.begin(), nodesAGM.end(), w) != nodesAGM.end();
                        if((estaV && !estaW) || (!estaV && estaW)){
                            if(vw.weight < minEdge.weight){
                                minEdge = vw;
                                isV_InMin = estaV;
                            }
                        }
                    }
                }

                // Agrego arista al AGM
                edgesAGM.insert(minEdge);

                // Agrego nodo al AGM
                if (!isV_InMin)
                    nodesAGM.insert(minEdge.n1);
                else
                    nodesAGM.insert(minEdge.n2);
                
                // Actualizo la suma de los pesos
                sum += minEdge.weight;
                i++;
            }

            // Ver aristas del AGM
            // for(Edge& vw: edgesAGM){
            //     cout << "(";
            //     cout << vw.n1.key << ", ";
            //     cout << vw.n2.key << "): " << vw.weight << endl;
            // }
            // cout << endl;

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