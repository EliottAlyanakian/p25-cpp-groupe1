#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex;
struct Edge{
    double value;
    Vertex* begin;
    Vertex* end;
    
    Edge(double v, Vertex* b, Vertex* e) : value(v), begin(b), end(e) {}
};

struct Vertex{
    int name;
    std::vector<Edge*> v;
    
    Vertex(int n) : name(n) {}
    
    void printV(){
        std::cout << "Vertex " << name << " est connecté à: ";
        for (int k = 0; k < v.size(); k++){
            std::cout << v[k]->end->name << " avec valeur d'arête : " << v[k]->value << " ";
        }
        std::cout << std::endl;
    }
};

struct graph{
    std::vector<Vertex*> sommet;
    
    void add_Edge(int begin, int end, double value){
        while (sommet.size() <= std::max(begin, end)){
            Vertex* newVertex = new Vertex(sommet.size());
            sommet.push_back(newVertex);
        }
        
        Edge* edge = new Edge(value, sommet[begin], sommet[end]);
        sommet[begin]->v.push_back(edge);
    }
    
    void print(){
        for (int k = 0; k < sommet.size(); k++){
            sommet[k]->printV();
        }
    }
};

int main(){
    graph g;
    g.add_Edge(2, 5, 17.9);
    g.add_Edge(5, 3, 23.9);
    g.add_Edge(3, 4, 16.9);
    g.add_Edge(4, 0, 699.9);
    g.print();
    return 0;
}