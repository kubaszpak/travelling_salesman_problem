#ifndef GENETIC_H
#define GENETIC_H

#include <iostream>
#include <cassert>
#include "adjency_matrix.h"

struct Path
{
    std::vector<int> route;
    int cost;

    Path()
    {
        cost = 0;
    }

    Path(int cost)
    {
        this->cost = cost;
    }

    Path(std::vector<int> &route)
    {
        this->route = route;
        this->cost = 0;
    }

    Path(int cost, std::vector<int> &route)
    {
        this->cost = cost;
        this->route = route;
    }

    bool operator<(const Path &path) const
    {
        return this->cost < path.cost;
    }
};

class genetic
{

public:
    genetic(adjency_matrix &matrix);
    int calculate_tour_cost(const std::vector<int> &path) const;
    std::vector<int> random_initial();
    void run();
    void print_population() const;
    void sort_population();
    std::vector<Path> create_mating_pool();
    std::vector<int> breed(Path &parent1, Path &parent2);
    std::vector<Path> breed_mating_pool(std::vector<Path> mating_pool);
    void mutate_single(std::vector<int> &route, double mutation_rate);
    void mutate_all(std::vector<Path> &mating_pool, double mutation_rate);
    void assign_tour_costs(std::vector<Path> &mating_pool);

private:
    std::vector<Path> population;
    adjency_matrix matrix;
    int number_of_vertices;
    int OPT;
    int max_int;
};

#endif /* GENETIC_H */