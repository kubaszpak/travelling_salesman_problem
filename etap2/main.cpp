#include <chrono>
#include <iostream>
#include "adjency_matrix.h"
#include "sa.h"

using namespace std;

int main()
{
    srand(time(NULL));
    // Time measurement
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    std::string file_name = "instances/ulysses22.tsp";

    adjency_matrix matrix = adjency_matrix(file_name);
    // matrix.print();
    sa(matrix).simulated_annealing();
    // std::vector<int> path{3, 17, 21, 16, 1, 2, 15, 11, 12, 13, 6, 5, 18, 19, 20, 9, 8, 10, 4, 14, 7, 0};
    // std::cout << sa(matrix).calculate_tour_cost(path) << std::endl;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    return 0;
}