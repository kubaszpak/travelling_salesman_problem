#ifndef SA_H
#define SA_H

#include "adjency_matrix.h"
#include <cassert>
#include <cmath>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <thread>

struct Node
{
    adjency_matrix matrix;
    int start_vertex;
    int cost;
    int level;
    std::vector<int> path;

    Node() {}

    Node(const adjency_matrix &matrix, int vertex)
    {
        this->matrix = adjency_matrix(matrix);
        this->start_vertex = vertex;
        this->cost = 0;
        this->level = 0;
        this->path.push_back(start_vertex);
    }

    void print()
    {
        std::cout << "Node - cost: " << this->cost << std::endl
                  << "Start vertex: " << this->start_vertex << std::endl;
        this->traceback();
    }

    void traceback()
    {
        std::cout << "Path: ";
        for (int i = 0; i < this->path.size(); i++)
        {
            std::cout << this->path[i] << " ";
        }
        if (level == matrix.number_of_vertices - 1)
            std::cout << start_vertex;
        std::cout << std::endl;
    }
};

class sa
{
public:
    sa();
    sa(const adjency_matrix &matrix);
    Node nearest_neighbour();
    void simulated_annealing();
    double prob(int candidate_cost);
    int calculate_tour_cost(std::vector<int> const &path);
    std::vector<int> inverse(int start, int offset);
    std::vector<int> swap(int i, int j);
    void check(std::vector<int> const &candidate, int k, int m);
    Node random_initial();

private:
    std::vector<int> best_solution;
    int best_cost;
    std::vector<int> current_solution;
    int current_cost;
    adjency_matrix cost_matrix;
    double temperature;
    int initial_cost;
};

#endif /* SA_H */