#ifndef ADJENCY_MATRIX_H
#define ADJENCY_MATRIX_H

#include <limits>
#include <iostream>
#include <cstddef>
#include <vector>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <string>

class adjency_matrix
{
public:
    adjency_matrix();
    ~adjency_matrix();
    adjency_matrix(const adjency_matrix &adjency_matrix);
    adjency_matrix(std::string file_name, bool is_directed = true);
    int get(int i, int j) const;
    void fill_with_inifinites(int number_of_vertices);
    void print() const;
    void delete_vector();
    bool is_empty();

    int number_of_vertices;
    int OPT;
    static int max_int;

private:
    std::vector<std::vector<int>> matrix;
};

#endif /* ADJENCY_MATRIX_H */