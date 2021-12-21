#include <chrono>
#include <iostream>
#include "adjency_matrix.h"
#include "sa.h"

using namespace std;

int main()
{
    srand(time(NULL));
    // Time measurement

    std::string filenames[] = {"instances/br17.atsp", "instances/gr24.tsp", "instances/ftv33.atsp", "instances/ftv38.atsp", "instances/ftv44.atsp", "instances/gr48.tsp", "instances/berlin52.tsp", "instances/brazil58.tsp"};

    for (int i = 7; i < 8; i++)
    {
        std::cout << "Instance: " << i << " " << filenames[i] << std::endl;
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        adjency_matrix matrix = adjency_matrix(filenames[i]);
        sa(matrix).simulated_annealing();
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
        cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;
    }

    return 0;
}