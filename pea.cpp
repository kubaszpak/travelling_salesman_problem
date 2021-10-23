#include "AdjencyMatrix.h"
#include <chrono>

using namespace std;

int main()
{

    std::string file_name = "instances/m11.atsp";
    AdjencyMatrix matrix = AdjencyMatrix(file_name);
    matrix.print();

    // cout << "Pierwszy rząd, pierwsza kolumna: " << matrix.get(0, 0) << endl;
    // cout << "Wartosc optymalna: " << matrix.OPT << endl;

    // Pomiar czasu

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    matrix.brute_force_tsp();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;

    return 0;
}