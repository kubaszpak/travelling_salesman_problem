#include "adjency_matrix.h"
#include "branch_and_bound.h"
#include <chrono>

using namespace std;

int main()
{

    // std::string files[9] = {
    //     "instances/m6.atsp",
    //     "instances/m8.atsp",
    //     "instances/m9.atsp",
    //     "instances/m10.atsp",
    //     "instances/m11.atsp",
    //     "instances/m12.atsp",
    //     "instances/m13.atsp",
    //     "instances/m14.atsp",
    //     "instances/m15.atsp"};

    // std::string files[2] = {
    //     "instances/br17.atsp",
    //     "instances/gr17.tsp"};

    // std::string files[1] = {
    //     "instances/br17.atsp"};

    // std::string file_name = "instances/m10.atsp";
    std::string file_name = "instances/gr17.tsp";
    // for (int i = 0; i < 1; i++)
    // {
    // file_name = files[i];

    adjency_matrix matrix = adjency_matrix(file_name);

    // Time measurement
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // In order to run one of the algorithms, uncomment one of the following lines

    // matrix.brute_force_tsp_set_first();
    branch_and_bound::branch_and_bound_tsp(matrix);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    // }

    return 0;
}