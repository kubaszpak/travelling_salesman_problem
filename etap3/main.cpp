#include <iostream>
#include "adjency_matrix.h"
#include "genetic.h"

int main()
{
    srand(time(NULL));

    adjency_matrix matrix = adjency_matrix("instances/m16.atsp");

    genetic genetic(matrix);
    genetic.run();
    return 0;
}