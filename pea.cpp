#include "AdjencyMatrix.h"

using namespace std;

int main()
{

    std::string file_name = "instances/m6.atsp";
    AdjencyMatrix matrix = AdjencyMatrix(file_name);
    matrix.print();

    // cout << "Pierwszy rząd, pierwsza kolumna: " << matrix.get(0, 0) << endl;
    cout << "Wartosc optymalna: " << matrix.OPT << endl;

    matrix.brute_force_tsp();

    return 0;
}