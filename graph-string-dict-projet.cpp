#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>    //pour l'initialisation de la matrice d'adjacence pour l'algorithme de Floyd-Warshall
#include <algorithm> //pour l'utilisation de std::min dans l'algorithme de Floyd-Warshall

class Matrice
{
    friend class Graph;
    friend class Vertex;
    friend class Edge;

private:
    double *tbl;
    int rows;
    int cols;

public:
    Matrice(int r, int c) : rows(r), cols(c)
    {
        tbl = new double[rows * cols]();
        for (int i = 0; i < rows * cols; i++)
        {
            tbl[i] = std::numeric_limits<double>::infinity(); // les arêtes qui n'existent pas ont pour valeur l'infini pour l'algorithme de Floyd-Warshall
        }
    }

    void set(int i, int j, double value)
    {
        tbl[i * cols + j] = value;
    }

    double get(int i, int j)
    {
        return tbl[i * cols + j];
    }

    void print() // IA utilisée pour cette méthode
    {
        std::cout << "[";
        for (int i = 0; i < rows; ++i)
        {
            if (i > 0)
                std::cout << " ";
            std::cout << "[";
            for (int j = 0; j < cols; ++j)
            {
                std::cout << tbl[i * cols + j];
                if (j < cols - 1)
                    std::cout << ", ";
            }
            std::cout << "]";

            if (i < rows - 1)
                std::cout << "\n";
        }
        std::cout << "]" << std::endl;
    }

    ~Matrice()
    {
        delete[] tbl;
    }
};

class Vertex;

class Edge
{
    friend class Vertex;
    friend class Graph;

private:
    double value;
    Vertex *begin;
    Vertex *end;

public:
    Edge(double val, Vertex *b, Vertex *e) : value(val), begin(b), end(e) {}
};

class Vertex
{
    friend class Graph;
    friend class Edge;

private:
    std::string name;
    std::vector<Edge *> edges;

public:
    Vertex(const std::string &n) : name(n) {}

    void dfsV(std::set<std::string> &visited)
    {
        if (visited.find(name) != visited.end())
            return; // j'ai utilisé l'IA pour savoir qu'il fallait mettre return comme condition d'arrêt dans cette méthode récursive
        visited.insert(name);
        std::cout << name << std::endl;
        for (int k = 0; k < edges.size(); k++)
        {
            edges[k]->end->dfsV(visited);
        }
    }
    ~Vertex()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            delete edges[i];
        }
    }
};

class Graph
{
    friend class Edge;
    friend class Vertex;

private:
    std::vector<Vertex *> sommet;
    Matrice *Adjacence = nullptr;
    std::unordered_map<std::string, int> srt_to_indice;

public:
    void add_edge(const std::string &begin, const std::string &end, double value)
    {
        std::unordered_map<std::string, int>::iterator search_begin = srt_to_indice.find(begin);
        std::unordered_map<std::string, int>::iterator search_end = srt_to_indice.find(end);

        if (search_begin == srt_to_indice.end()) // begin n'existe pas
        {
            Vertex *begin_vertex = new Vertex(begin);
            sommet.push_back(begin_vertex);
            srt_to_indice[begin] = sommet.size() - 1;
        }
        if (search_end == srt_to_indice.end()) // end n'existe pas
        {
            Vertex *end_vertex = new Vertex(end);
            sommet.push_back(end_vertex);
            srt_to_indice[end] = sommet.size() - 1;
        }
        Edge *new_edge = new Edge(value, sommet[srt_to_indice[begin]], sommet[srt_to_indice[end]]);
        sommet[srt_to_indice[begin]]->edges.push_back(new_edge);
    }

    void dfs()
    {
        std::set<std::string> visited;
        sommet[0]->dfsV(visited);
    }

    void Matrice_Adj()
    {
        Adjacence = new Matrice(sommet.size(), sommet.size());
        for (auto &e : srt_to_indice)
        {
            for (int k = 0; k < sommet[std::get<1>(e)]->edges.size(); k++)
            {
                Vertex *sommet_courant = sommet[std::get<1>(e)];
                Adjacence->set(std::get<1>(e), srt_to_indice[sommet_courant->edges[k]->end->name], sommet_courant->edges[k]->value);
            }
        }
    }

    void print_adjacence()
    {
        if (Adjacence != nullptr)
        {
            Adjacence->print();
        }
    }

    void print_encodage()
    {
        for (auto &e : srt_to_indice)
        {
            std::cout << std::get<0>(e) << " -> " << std::get<1>(e) << std::endl;
        }
    }

    void Floyd_Warshall()
    {
        for (int k = 0; k < sommet.size(); k++)
        {
            for (int i = 0; i < sommet.size(); i++)
            {
                for (int j = 0; j < sommet.size(); j++)
                {
                    Adjacence->tbl[i * Adjacence->cols + j] = std::min(Adjacence->tbl[i * Adjacence->cols + j], Adjacence->tbl[i * Adjacence->cols + k] + Adjacence->tbl[k * Adjacence->cols + j]);
                }
            }
        }
    }

    void read_graph(const std::string &filename)
    {
        std::ifstream file(filename);
        if (not file.is_open())
        {
            throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
        }
        std::string from, to;
        double value;

        while (file >> from >> to >> value)
        {
            std::cout << from << " " << to << " " << value << std::endl;
            this->add_edge(from, to, value);
        }
        std::cout << std::endl;
        file.close();
    }

    ~Graph()
    {
        for (int i = 0; i < sommet.size(); i++)
        {
            delete sommet[i];
        }
        if (Adjacence != nullptr)
        {
            delete Adjacence;
        }
    }
};

int main()
{

    // LECTURE DU GRAPHE
    Graph g;
    g.read_graph("graph0.gr");
    std::cout << "DFS du graphe : " << std::endl;
    g.dfs();

    std::cout << "\nIndices de la matrice d'adjacence et leurs sommets correspondants " << std::endl;
    g.print_encodage();

    std::cout << "\nMatrice d'adjacence du graphe : " << std::endl;
    g.Matrice_Adj();
    g.print_adjacence();

    std::cout << "\nMatrice d'adjacence du graphe après application de l'algorithme de Floyd-Warshall : " << std::endl;
    g.Floyd_Warshall();
    g.print_adjacence();

    return 0;
}
