#include <iostream>
#include <vector>
#include <algorithm> // pour std::max

struct Vertex;

struct Edge
{
    double value;
    Vertex *begin;
    Vertex *end;
    Edge(double val, Vertex *b, Vertex *e) : value(val), begin(b), end(e) {}
};

struct Vertex
{
    int name;
    std::vector<Edge *> v;

    Vertex(int n) : name(n) {}

    void printV()
    {

        if (v.empty())
            return;

        std::cout << "Vertex " << name << " est connecté a : ";

        for (size_t k = 0; k < v.size(); k++)
        {
            std::cout << " -> " << v[k]->end->name
                      << " (poids: " << v[k]->value << ")";
        }
        std::cout << std::endl;
    }
};

struct Graph
{
    std::vector<Vertex *> sommet;

    void add_Edge(int beginId, int endId, double value)
    {
        // Si on veut ajouter une arête entre 2 et 5, il faut que le graphe aille au moins jusqu'à 5.
        int maxId = std::max(beginId, endId);

        while (sommet.size() <= maxId)
        {

            sommet.push_back(new Vertex(sommet.size()));
        }

        Vertex *startNode = sommet[beginId];
        Vertex *endNode = sommet[endId];

        Edge *newEdge = new Edge(value, startNode, endNode);

        startNode->v.push_back(newEdge);
    }

    void print()
    {
        for (size_t k = 0; k < sommet.size(); k++)
        {
            sommet[k]->printV();
        }
    }
    ~Graph()
    {
        for (Vertex *vert : sommet)
        {
            for (Edge *edge : vert->v)
                delete edge;
            delete vert;
        }
    }
};

int main()
{
    Graph g;

    // Le graphe va s'agrandir pour accueillir les indices 0, 2, 3, 4, 5
    g.add_Edge(2, 5, 17.9);
    g.add_Edge(5, 3, 23.9);
    g.add_Edge(4, 0, 699.9);

    g.print();

    return 0;
}
