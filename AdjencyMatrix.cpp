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

    int path_number = 0;

    do
    {
        std::cout << "Path " << path_number << " ";
        for (int i = 0; i < this->number_of_vertices; i++)
        {
            std::cout << paths[i] << " ";
        }
        std::cout << std::endl;
        path_number++;
    } while (std::next_permutation(paths.begin(), paths.end()));

    
}