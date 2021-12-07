#include "sa.h"

sa::sa() {}

sa::sa(const adjency_matrix &matrix)
{
    this->cost_matrix = matrix;
    Node initial = nearest_neighbour();
    this->best_cost = initial.cost;
    this->current_cost = initial.cost;
    this->best_solution = initial.path;
    this->current_solution = initial.path;
    this->temperature = std::numeric_limits<double>::max(); // 1.79769e+308
    this->initial_cost = initial.cost;
    double PRD = (double)(initial.cost - cost_matrix.OPT) * 100 / cost_matrix.OPT;
    std::cout << "K: 0 M: 0 " << initial.cost << " " << std::setprecision(2) << std::fixed << PRD << "%" << std::endl;
}

void print_path(std::vector<int> const &path)
{
    std::string best_path = "";
    for (int i = 0; i < path.size(); i++)
    {
        best_path.append(std::to_string(path[i]));

        best_path.append(" -> ");
    }
    best_path.append(std::to_string(path[0]));

    std::cout << best_path << std::endl;
}

Node sa::nearest_neighbour()
{
    Node node;
    Node best_node;
    int max_int = cost_matrix.max_int;
    best_node.cost = max_int;
    int number_of_vertices = cost_matrix.number_of_vertices;
    for (int i = 0; i < 1; i++)
    {
        node = Node(cost_matrix, i);
        int last_vertex = i;
        while (node.level != number_of_vertices - 1)
        {
            int smallest_cost_from_last_vertex = max_int;
            int smallest_cost_vertex = -1;
            for (int k = 0; k < number_of_vertices; k++)
            {
                // if (last_vertex == k)
                // {
                //     continue;
                // }
                int cost_from_last_vertex_to_k = node.matrix.get(last_vertex, k);

                if (cost_from_last_vertex_to_k < smallest_cost_from_last_vertex)
                {
                    smallest_cost_from_last_vertex = cost_from_last_vertex_to_k;
                    smallest_cost_vertex = k;
                }
            }
            assert(smallest_cost_vertex != -1);
            assert(smallest_cost_from_last_vertex != max_int);
            node.cost += smallest_cost_from_last_vertex;
            node.path.push_back(smallest_cost_vertex);
            node.level += 1;
            node.matrix.set_INF(last_vertex, smallest_cost_vertex, i);
            last_vertex = smallest_cost_vertex;
        }
        node.cost += cost_matrix.get(node.path[node.path.size() - 1], i);
        if (node.cost < best_node.cost)
        {
            best_node = node;
        }
    }
    // best_node.print();
    return best_node;
}

int sa::calculate_tour_cost(std::vector<int> const &path)
{
    int sum = 0;
    for (int i = 0; i < cost_matrix.number_of_vertices - 1; i++)
    {
        sum += cost_matrix.get(path[i], path[i + 1]);
    }
    sum += cost_matrix.get(path[cost_matrix.number_of_vertices - 1], path[0]);
    return sum;
}

double getRandom()
{
    return ((double)rand() / RAND_MAX);
}

int getRandomInt(int start, int n)
{
    return rand() % (n - start) + start;
}

std::vector<int> sa::inverse(int start, int offset)
{
    std::vector<int> new_solution = this->current_solution;
    std::reverse(new_solution.begin() + start + 1, new_solution.end() + (offset + 1 - new_solution.size()));
    print_path(new_solution);
    return new_solution;
}

std::vector<int> sa::swap(int i, int j)
{
    std::vector<int> new_solution = this->current_solution;
    int temp = new_solution[i];
    new_solution[i] = new_solution[j];
    new_solution[j] = temp;
    // print_path()
    return new_solution;
}

double sa::prob(int candidate_cost)
{
    return exp((-1) * (abs(candidate_cost - this->current_cost)) / this->temperature);
}

void sa::check(std::vector<int> const &candidate, int k, int m)
{
    int candidate_cost = calculate_tour_cost(candidate);
    if (candidate_cost < this->current_cost)
    {
        // std::cout << "1" << std::endl;
        this->current_cost = candidate_cost;
        this->current_solution = candidate;
        if (candidate_cost < this->best_cost)
        {
            // print_path(candidate);
            double PRD = (double)(candidate_cost - cost_matrix.OPT) * 100 / cost_matrix.OPT;
            std::cout << "K: " << k << " M: " << m << " " << candidate_cost << " " << std::setprecision(2) << std::fixed << PRD << "%" << std::endl;

            this->best_cost = candidate_cost;
            this->best_solution = candidate;
        }
    }
    else if (getRandom() < prob(candidate_cost))
    {
        // std::cout << "2" << std::endl;
        this->current_cost = candidate_cost;
        this->current_solution = candidate;
    }
}

void sa::simulated_annealing()
{
    // CONSTANTS
    double cooling_rate = 0.95; // alternatives [0,99+, 0,995]
    int number_of_vertices = cost_matrix.number_of_vertices;
    int K = 10000;
    int start_temperature = 1000;
    int m = 0;
    // int M = 1000;
    double temperature_stop_condition = 0.000001;

    for (int s = 0; s < K; ++s)
    {
        m = 0;
        // this->temperature = std::numeric_limits<double>::max(); // 1.79769e+308
        this->temperature = start_temperature;
        while (temperature > temperature_stop_condition)
        {
            // INVERSE
            // int start_city = getRandomInt(0, number_of_vertices - 2);
            // int offset = getRandomInt(start_city + 2, number_of_vertices);
            // // std::cout << "Swap cities start: " << start_city << " and offset: " << offset << std::endl;
            // std::vector<int> candidate = inverse(start_city, offset);

            // SWAP
            int i = -1;
            int j = -1;
            while (i == j)
            {
                i = getRandomInt(0, number_of_vertices - 1);
                j = getRandomInt(0, number_of_vertices - 1);
            }
            std::vector<int> candidate = swap(i, j);

            check(candidate, s, m);
            temperature = temperature * cooling_rate;
            m++;
        }
    }
    double PRD = (double)(initial_cost - cost_matrix.OPT) * 100 / cost_matrix.OPT;
    std::cout << "K: 0 M: 0 " << initial_cost << " " << std::setprecision(2) << std::fixed << PRD << "%" << std::endl;
    print_path(best_solution);
    return;
}