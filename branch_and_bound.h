#ifndef BRANCH_AND_BOUND_H
#define BRANCH_AND_BOUND_H

#include "adjency_matrix.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

struct Node
{
    Node *parent;
    adjency_matrix matrix;
    int cost;
    int vertex;
    int level;

    Node(const adjency_matrix &matrix)
    {
        this->matrix = adjency_matrix(matrix);
        this->parent = nullptr;
        this->vertex = 0;
        this->cost = 0;
    }

    Node(const adjency_matrix &matrix, int cost) : Node(matrix)
    {
        this->cost = cost;
    }

    void print()
    {
        std::cout << "Node - cost: " << this->cost << std::endl
                  << "Parent: " << this->parent->vertex
                  << std::endl
                  << "New vertex: " << this->vertex;
        this->matrix.print();
        std::cout << std::endl
                  << std::endl;
    }

    void traceback()
    {
        Node *node = (Node *)this;
        std::cout << "From the end: ";
        while (node->parent != nullptr)
        {
            std::cout << node->vertex << " ";
            node = node->parent;
        }
        std::cout << std::endl;
    }
};

class branch_and_bound
{
public:
    static void branch_and_bound_tsp();
};

#endif /* BRANCH_AND_BOUND_H */