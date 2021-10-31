#include "AdjencyMatrix.h"

int AdjencyMatrix::max_int = std::numeric_limits<int>::max();

AdjencyMatrix::AdjencyMatrix()
{
}

AdjencyMatrix::AdjencyMatrix(std::string file_name, bool is_directed)
{
    // std::cout << is_directed << std::endl;
    std::ifstream file(file_name);

    std::string name;

    int edge_weight;

    if (file.is_open())
    {
        file >> name;
        file >> this->number_of_vertices;

        fill_with_inifinites(number_of_vertices);

        if (file.fail())
        {
            std::cout << "File error - READ SIZE" << std::endl;
        }
        else
        {
            for (int i = 0; i < this->number_of_vertices; i++)
            {

                for (int j = 0; j < this->number_of_vertices; j++)
                {
                    file >> edge_weight;

                    if (file.fail())
                    {
                        std::cout << "File error - READ DATA" << std::endl;
                        return;
                    }
                    else
                    {
                        matrix[i][j] = edge_weight;
                        if (!is_directed)
                        {
                            matrix[i][j] = edge_weight;
                        }
                    }
                }
            }

            file >> this->OPT;
        }
        file.close();
    }
    else
    {
        std::cout << "File error - OPEN" << std::endl;
        return;
    }
}

AdjencyMatrix::~AdjencyMatrix()
{
    delete_vector();
}

void AdjencyMatrix::fill_with_inifinites(int number_of_vertices)
{
    matrix.resize(number_of_vertices, std::vector<int>(number_of_vertices, AdjencyMatrix::max_int));
}

void AdjencyMatrix::delete_vector()
{
    matrix.clear();
}

bool AdjencyMatrix::is_empty()
{
    return matrix.empty();
}

int AdjencyMatrix::get(int i, int j)
{
    return this->matrix[i][j];
}

void AdjencyMatrix::print()
{
    std::cout << std::endl
              << "--- AdjencyMatrix ---" << std::endl;
    std::cout << "      ";
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < number_of_vertices; i++)
    {
        std::cout << std::setw(3) << i << "   ";
        for (int j = 0; j < number_of_vertices; j++)
        {
            if (matrix[i][j] != AdjencyMatrix::max_int)
            {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            else
            {
                std::cout << "Inf"
                          << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void AdjencyMatrix::brute_force_tsp()
{

    std::vector<int> paths;

    for (int i = 0; i < this->number_of_vertices; i++)
    {
        paths.push_back(i);
    }

    // int iteration_number = 0;
    // std::string first_path;
    // bool first_was_found = false;

    std::string current_best_path;
    int current_best_path_cost = std::numeric_limits<int>::max();
    int cost;
    int first_cost = 0;
    double PRD;

    // doing first computation twice for better performance
    for (int i = 1; i < number_of_vertices; i++)
    {
        first_cost += matrix[paths[i - 1]][paths[i]];
    }

    first_cost += matrix[paths[number_of_vertices - 1]][paths[0]];

    do
    {
        // To print all paths uncomment this and iteration_number initialization from above

        // std::cout << "Path " << iteration_number << " ";
        // for (int i = 0; i < this->number_of_vertices; i++)
        // {
        //     std::cout << paths[i] << " ";
        // }
        // std::cout << std::endl;
        // iteration_number++;

        cost = 0;
        for (int i = 1; i < number_of_vertices; i++)
        {
            cost += matrix[paths[i - 1]][paths[i]];
        }

        cost += matrix[paths[number_of_vertices - 1]][paths[0]];

        // Cleaner solution
        // if (!first_was_found)
        // {
        //     first_cost = cost;
        //     first_was_found = true;
        // }

        if (current_best_path_cost > cost)
        {

            // To keep track of best path
            current_best_path = "";
            for (int i = 0; i < number_of_vertices; i++)
            {
                current_best_path.append(std::to_string(paths[i]));

                // if (i != number_of_vertices - 1)
                current_best_path.append(" -> ");
            }
            current_best_path.append(std::to_string(paths[0]));

            std::cout << current_best_path << std::endl;

            PRD = (double)(cost - this->OPT) * 100 / this->OPT;
            std::cout << cost << " " << std::setprecision(2) << std::fixed << PRD << "%" << std::endl;
            current_best_path_cost = cost;
        }

    } while (std::next_permutation(paths.begin(), paths.end()));

    PRD = (first_cost - this->OPT) * 100.0 / this->OPT;
    std::cout << first_cost << " " << std::setprecision(2) << PRD << "%" << std::endl;

    std::cout << current_best_path << std::endl;
}

void AdjencyMatrix::brute_force_tsp_set_first()
{

    std::vector<int> paths;

    for (int i = 1; i < this->number_of_vertices; i++)
    {
        paths.push_back(i);
    }

    // int iteration_number = 0;
    // std::string first_path;
    // bool first_was_found = false;

    std::string current_best_path = "";
    int current_best_path_cost = std::numeric_limits<int>::max();
    int cost;
    int first_cost = 0;
    double PRD;

    // doing first computation twice for better performance
    first_cost += matrix[0][paths[0]];
    for (int i = 1; i < number_of_vertices - 1; i++)
    {
        first_cost += matrix[paths[i - 1]][paths[i]];
    }

    first_cost += matrix[paths[number_of_vertices - 2]][0];
    /* current_best_path_cost = first_cost; this line itroduces a problem
    when first path is the best then string current_best_path would be empty at the end */

    do
    {
        // To print all paths uncomment this and iteration_number initialization from above

        // std::cout << "Path " << iteration_number << " ";
        // for (int i = 0; i < this->number_of_vertices; i++)
        // {
        //     std::cout << paths[i] << " ";
        // }
        // std::cout << std::endl;
        // iteration_number++;

        cost = 0;
        cost += matrix[0][paths[0]];
        for (int i = 1; i < number_of_vertices - 1; i++)
        {
            cost += matrix[paths[i - 1]][paths[i]];
        }

        cost += matrix[paths[number_of_vertices - 2]][0];

        // Cleaner solution
        // if (!first_was_found)
        // {
        //     first_cost = cost;
        //     first_was_found = true;
        // }

        if (current_best_path_cost > cost)
        {

            // To keep track of best path
            current_best_path = "";
            current_best_path.append("0 -> ");
            for (int i = 0; i < number_of_vertices - 1; i++)
            {
                current_best_path.append(std::to_string(paths[i]));

                // if (i != number_of_vertices - 1)
                current_best_path.append(" -> ");
            }
            current_best_path.append("0");

            std::cout << current_best_path << std::endl;

            PRD = (double)(cost - this->OPT) * 100 / this->OPT;
            std::cout << cost << " " << std::setprecision(2) << std::fixed << PRD << "%" << std::endl;
            current_best_path_cost = cost;
        }

    } while (std::next_permutation(paths.begin(), paths.end()));

    PRD = (first_cost - this->OPT) * 100.0 / this->OPT;
    std::cout << first_cost << " " << std::setprecision(2) << PRD << "%" << std::endl;

    std::cout << current_best_path << std::endl;
}
