// graph_string_dict_projet_IA.cpp

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <iomanip> // Cette bibliothèque est utilisé pour std::setw() (set width).
// Elle permet de formater l'affichage de la matrice (Floyd-Warshall) en colonnes 
// parfaitement alignées

// Pré-déclaration pour les amitiés (friend)
class Graph;
class Vertex;


class Edge
{
    friend class Vertex;
    friend class Graph;

private:
    int target_vertex_idx; // Indice du sommet d'arrivée dans le vecteur du Graphe
    double weight;         // Poids de l'arête

    Edge(int target, double w) : target_vertex_idx(target), weight(w) {}
};


class Vertex
{
    friend class Graph;

private:
    std::string name;
    std::vector<Edge*> edges; // Vecteur de pointeurs d'arêtes 

    Vertex(const std::string& n) : name(n) {}

    // Destructeur pour nettoyer les arêtes allouées avec new
    ~Vertex() {
        for (Edge* e : edges) {
            delete e;
        }
        edges.clear();
    }
};


class Graph
{
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> name_to_index;
    // On utilise un vector de vector de double comme matrice
    std::vector<std::vector<double>> adj_matrix;

    // Helper pour récupérer ou créer un index de sommet
    int get_or_create_index(const std::string& name) {
        if (name_to_index.find(name) == name_to_index.end()) {
            // Le sommet n'existe pas, on le crée
            int new_index = static_cast<int>(vertices.size());
            vertices.push_back(new Vertex(name));
            name_to_index[name] = new_index;
            return new_index;
        }
        return name_to_index[name];
    }

    // Helper récursif pour le DFS
    void dfs_recursive(int u_idx, std::set<int>& visited) {
        visited.insert(u_idx);
        std::cout << vertices[u_idx]->name << " ";

        // On parcourt les arêtes de ce sommet
        for (Edge* edge : vertices[u_idx]->edges) {
            if (visited.find(edge->target_vertex_idx) == visited.end()) {
                dfs_recursive(edge->target_vertex_idx, visited);
            }
        }
    }

public:
    // Destructeur pour nettoyer les sommets alloués avec new
    ~Graph() {
        for (Vertex* v : vertices) {
            delete v;
        }
        vertices.clear();
    }

    // Ajout d'une arête
    void add_edge(const std::string &begin, const std::string &end, double value) {
        int u_idx = get_or_create_index(begin);
        int v_idx = get_or_create_index(end);

        Edge* new_edge = new Edge(v_idx, value);
        vertices[u_idx]->edges.push_back(new_edge);
    }

    void dfs() {
        std::cout << "--- Parcours DFS ---" << std::endl;
        std::set<int> visited;
        
        // La boucle assure de visiter même les composantes non connectées
        // Si on veut partir uniquement du premier sommet inséré, on retire la boucle
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (visited.find(i) == visited.end()) {
                dfs_recursive(i, visited);
            }
        }
        std::cout << std::endl << std::endl;
    }

    void build_adjacency_matrix() {
        size_t n = vertices.size();
        double INF = std::numeric_limits<double>::infinity();

        // Initialisation n x n avec INF partout, et 0 sur la diagonale
        adj_matrix.assign(n, std::vector<double>(n, INF));
        for (size_t i = 0; i < n; ++i) {
            adj_matrix[i][i] = 0.0;
        }

        for (size_t i = 0; i < n; ++i) {
            for (Edge* e : vertices[i]->edges) {
                // On prend le min au cas où il y aurait plusieurs arêtes entre deux mêmes sommets
                if (e->weight < adj_matrix[i][e->target_vertex_idx]) {
                     adj_matrix[i][e->target_vertex_idx] = e->weight;
                }
            }
        }
    }

    void floyd_warshall() {
        build_adjacency_matrix();
        
        size_t n = adj_matrix.size();
        // On copie la matrice d'adjacence dans la matrice de distances
        std::vector<std::vector<double>> dist = adj_matrix;


        for (size_t k = 0; k < n; ++k) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (dist[i][k] != std::numeric_limits<double>::infinity() &&
                        dist[k][j] != std::numeric_limits<double>::infinity()) {
                        
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }

        // Affichage des résultats
        std::cout << "--- Floyd-Warshall (Plus courts chemins) ---" << std::endl;
        // En-tête avec les noms (tronqués pour l'affichage)
        std::cout << std::setw(10) << " ";
        for (size_t i = 0; i < n; ++i) {
            std::cout << std::setw(10) << vertices[i]->name.substr(0, 9);
        }
        std::cout << std::endl;

        for (size_t i = 0; i < n; ++i) {
            std::cout << std::setw(10) << vertices[i]->name.substr(0, 9);
            for (size_t j = 0; j < n; ++j) {
                if (dist[i][j] == std::numeric_limits<double>::infinity()) {
                    std::cout << std::setw(10) << "INF";
                } else {
                    std::cout << std::setw(10) << dist[i][j];
                }
            }
            std::cout << std::endl;
        }
    }

    void read_from_file(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier " + filename);
        }

        std::string from, to;
        double value;
        while (file >> from >> to >> value) {
            add_edge(from, to, value);
        }
        file.close();
    }
};


int main()
{
    try {
        Graph g;
        g.read_from_file("graph0.gr");

        // TEST DFS
        g.dfs();

        // TEST FLOYD-WARSHALL
        g.floyd_warshall();

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
