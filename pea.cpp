#include "adjency_matrix.h"
#include "branch_and_bound.h"
#include <chrono>

using namespace std;

int main()
{

    // std::string file_name = "instances/m12.atsp";
    // adjency_matrix matrix = adjency_matrix(file_name);
    // matrix.print();

    // Pomiar czasu

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // matrix.brute_force_tsp();
    branch_and_bound::branch_and_bound_tsp();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;

    return 0;
}