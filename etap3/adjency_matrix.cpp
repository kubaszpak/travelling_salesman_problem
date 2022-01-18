#include "adjency_matrix.h"

int adjency_matrix::max_int = std::numeric_limits<int>::max();

adjency_matrix::adjency_matrix()
{
}

adjency_matrix::adjency_matrix(const adjency_matrix &adjency_matrix)
{
    this->matrix = adjency_matrix.matrix;
    this->number_of_vertices = adjency_matrix.number_of_vertices;
    this->OPT = adjency_matrix.OPT;
}

adjency_matrix::adjency_matrix(std::string file_name, bool is_directed)
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
                        if (i == j)
                        {
                            matrix[i][j] = max_int;
                        }
                        else
                        {
                            matrix[i][j] = edge_weight;
                        }

                        if (!is_directed)
                        {
                            matrix[j][i] = edge_weight;
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

adjency_matrix::~adjency_matrix()
{
    delete_vector();
}

void adjency_matrix::fill_with_inifinites(int number_of_vertices)
{
    matrix.resize(number_of_vertices, std::vector<int>(number_of_vertices, adjency_matrix::max_int));
}

void adjency_matrix::delete_vector()
{
    matrix.clear();
}

bool adjency_matrix::is_empty()
{
    return matrix.empty();
}

int adjency_matrix::get(int i, int j) const
{
    return this->matrix[i][j];
}

void adjency_matrix::print() const
{
    std::cout << std::endl
              << "--- adjency_matrix ---" << std::endl;
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
            if (matrix[i][j] != adjency_matrix::max_int)
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