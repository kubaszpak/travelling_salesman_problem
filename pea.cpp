#include "adjency_matrix.h"
#include "branch_and_bound.h"
#include <chrono>

using namespace std;

int main()
{

    std::string file_name = "instances/m15.atsp";

    // Pomiar czasu
    // matrix.print();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // adjency_matrix matrix = adjency_matrix(file_name);
    // matrix.brute_force_tsp_set_first();
    branch_and_bound::branch_and_bound_tsp_fixed(file_name);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;

    return 0;
}