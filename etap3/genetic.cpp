#include "genetic.h"

const int pop_size = 300;
const int elite_size = 30;
const int number_of_generations = 20000;
const double mutation_rate = 0.02;

// const int pop_size = 5;
// const int elite_size = 3;
// const int number_of_generations = 3;
// const double mutation_rate = 0.01;

genetic::genetic(adjency_matrix &matrix)
{
    this->matrix = adjency_matrix(matrix);
    number_of_vertices = matrix.number_of_vertices;
    max_int = matrix.max_int;
    OPT = matrix.OPT;
}

void print_path(const std::vector<int> &path)
{
    std::cout << "Path: ";
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i] << " ";
    }

    std::cout << "\n";
}

std::vector<int> genetic::random_initial()
{
    std::vector<int> path;

    path.push_back(0);

    for (int i = 1; i < number_of_vertices; i++)
    {
        path.push_back(i);
    }

    path.push_back(0);

    std::random_shuffle(path.begin() + 1, path.end() - 1);

    return path;
}

int genetic::calculate_tour_cost(const std::vector<int> &path) const
{
    int sum = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        sum += matrix.get(path[i], path[i + 1]);
    }
    return sum;
}

void genetic::print_population() const
{
    for (auto const &path : population)
    {
        print_path(path.route);
        std::cout << "Cost: " << path.cost << std::endl;
        // std::cout << "Adres path.route: " << &path.route << std::endl;
    }
}

void genetic::sort_population()
{
    std::sort(population.begin(), population.end());
}

double get_random()
{
    return ((double)rand() / RAND_MAX);
}

std::vector<Path> genetic::create_mating_pool()
{
    std::vector<Path> mating_pool;
    for (int i = 0; i < elite_size; i++)
    {
        mating_pool.push_back(population.at(i));
    }

    assert(population.size() == pop_size);
    assert(pop_size >= elite_size);

    // std::cout << "Population size: " << population.size() << std::endl;
    // std::cout << "Mating pool size: " << mating_pool.size() << std::endl;
    int first_cost = population.at(0).cost;
    int last_cost = population.at(population.size() - 1).cost;

    for (int i = 0; i < population.size() - elite_size; i++)
    {
        double random = get_random();
        for (int j = 0; j < population.size(); j++)
        {
            int cost = population.at(j).cost;
            double probability = (double)(last_cost - cost) / (last_cost - first_cost);

            if (probability < random)
            {
                // std::cout << "Cost: " << cost << std::endl;
                // std::cout << "Probability: " << probability << std::endl;
                mating_pool.push_back(population.at(j));
                break;
            }
        }
    }

    return mating_pool;
}

std::vector<int> genetic::breed(Path &parent1, Path &parent2)
{
    std::vector<int> child;

    assert(parent1.route.size() == parent2.route.size() && parent1.route.size() == number_of_vertices + 1);

    int gene1 = 0;
    int gene2 = 0;

    while (gene1 == gene2)
    {
        gene1 = rand() % number_of_vertices + 1; // dla 7 miast: przedział losowania: 1 - 7; indexy wektora: 0-7, użytkowe 1-6
        gene2 = rand() % number_of_vertices + 1; // dla 8 miast: przedział losowania 1 - 8; indexy wektora: 0-8, użytkowe 1-7
    }

    int start = std::min(gene1, gene2);
    int end = std::max(gene1, gene2);

    // std::cout << "gene1: " << gene1 << " gene2: " << gene2 << std::endl;
    // std::cout << "start: " << start << " end: " << end << std::endl;
    // print_path(parent1.route);
    // print_path(parent2.route);

    child.push_back(0);

    for (int i = start; i < end; i++)
    {
        child.push_back(parent1.route.at(i));
    }

    for (int i = 1; i < number_of_vertices; i++)
    {
        if (std::find(child.begin(), child.end(), parent2.route.at(i)) == child.end())
        {
            child.push_back(parent2.route.at(i));
        }
    }

    child.push_back(0);

    // std::cout << "Result: " << std::endl;
    // print_path(child);

    return child;
}

std::vector<Path> genetic::breed_mating_pool(std::vector<Path> mating_pool)
{
    std::vector<Path> new_mating_pool;

    for (int i = 0; i < elite_size; i++)
    {
        new_mating_pool.push_back(mating_pool.at(i));
    }

    for (int i = 0; i < mating_pool.size() - elite_size; i++)
    {
        std::vector<int> new_route = breed(mating_pool.at(i), mating_pool.at(mating_pool.size() - i - 1));
        new_mating_pool.push_back(Path(new_route));
    }

    return new_mating_pool;
}

void print_mating_pool(const std::vector<Path> &mating_pool)
{
    for (auto const &path : mating_pool)
    {
        print_path(path.route);
        std::cout << "Cost: " << path.cost << std::endl;
    }
}

void genetic::mutate_single(std::vector<int> &route, double mutation_rate)
{
    assert(route.size() == number_of_vertices + 1);
    for (int i = 1; i < route.size() - 1; i++)
    {
        if (get_random() < mutation_rate)
        {
            int second_index = rand() % (number_of_vertices - 1) + 1;

            int temp = route[second_index];
            route[second_index] = route[i];
            route[i] = temp;
        }
    }
}

void genetic::mutate_all(std::vector<Path> &mutation_pool, double mutation_rate)
{
    for (int i = 0; i < mutation_pool.size(); i++)
    {
        mutate_single(mutation_pool.at(i).route, mutation_rate);
    }
}

void genetic::assign_tour_costs(std::vector<Path> &mating_pool)
{
    for (Path &path : mating_pool)
    {
        path.cost = calculate_tour_cost(path.route);
    }
}

void genetic::run()
{
    matrix.print();
    for (int i = 0; i < pop_size; i++)
    {
        std::vector<int> randomPath = random_initial();
        population.push_back(Path(calculate_tour_cost(randomPath), randomPath));
    }

    std::cout << "First answer: " << population.at(0).cost << std::endl;

    std::vector<Path> mating_pool;
    for (int i = 0; i < number_of_generations; i++)
    {
        sort_population();
        // std::cout << "Sorted population: " << std::endl;
        // print_population();
        mating_pool = create_mating_pool();
        // std::cout << "-------------------" << std::endl;
        // std::cout << "Mating pool: " << std::endl;
        // print_mating_pool(mating_pool);
        mating_pool = breed_mating_pool(mating_pool);
        // std::cout << "-------------------" << std::endl;
        // std::cout << "Mating pool after breeding: " << std::endl;
        // print_mating_pool(mating_pool);
        mutate_all(mating_pool, mutation_rate);
        // std::cout << "-------------------" << std::endl;
        // std::cout << "Mating pool after mutation: " << std::endl;
        // print_mating_pool(mating_pool);
        assign_tour_costs(mating_pool);
        // std::cout << "-------------------" << std::endl;
        // std::cout << "Mating pool after assigning tour costs: " << std::endl;
        // print_mating_pool(mating_pool);
        population = mating_pool;
    }

    sort_population();

    std::cout << "Final answer: "
              << population.at(0).cost << std::endl;
}