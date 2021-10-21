#ifndef ADJENCY_MATRIX_H
#define ADJENCY_MATRIX_H

#include <limits>
#include <iostream>
#include <cstddef>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

class AdjencyMatrix
{
public:
    AdjencyMatrix();
    ~AdjencyMatrix();
    AdjencyMatrix(std::string file_name, bool is_directed = true);
    int get(int i, int j);
    void fill_with_inifinites(int number_of_vertices);
    void print();
    void delete_vector();
    bool is_empty();
    int OPT;
    void brute_force_tsp();

private:
    std::vector<std::vector<int>> matrix;
    int number_of_vertices;
    static int max_int;
};

#endif /* ADJENCY_MATRIX_H */