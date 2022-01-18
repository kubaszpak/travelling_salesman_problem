#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include "adjency_matrix.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

struct Node
{
    adjency_matrix matrix;
    int cost;
    int vertex;
    int level;
    std::vector<int> path;

    Node(const adjency_matrix &matrix)
    {
        this->matrix = adjency_matrix(matrix);
        this->vertex = 0;
        this->cost = 0;
    }

    Node(const adjency_matrix &matrix, int cost) : Node(matrix)
    {
        this->cost = cost;
    }

    void print()
    {
        int parent = (this->path.size() > 1) ? this->path[this->path.size() - 2] : -1;
        std::cout << "Node - cost: " << this->cost << std::endl
                  << "Parent: " << parent << std::endl
                  << "New vertex: " << this->vertex;
        this->matrix.print();
    }

    void traceback()
    {
        std::cout << "Path: ";
        for (int i = 0; i < this->path.size(); i++)
        {
            std::cout << this->path[i] << " ";
        }
        if (level == matrix.number_of_vertices - 1)
            std::cout << "0";
        std::cout << std::endl;
    }
};

class branch_and_bound
{
public:
    static void branch_and_bound_tsp(adjency_matrix &matrix);
    static void branch_and_bound_tsp_fixed(adjency_matrix &matrix);
};

#endif /* BRANCH_AND_BOUND_H */