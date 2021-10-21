#include "AdjencyMatrix.h"

using namespace std;

int main()
{
    cout << "Hello world" << endl;

    std::string file_name = "instances/m6.atsp";
    AdjencyMatrix matrix = AdjencyMatrix(file_name);
    // matrix.print();

    cout << "Ostatni rzad, pierwsza kolumna: " << matrix.get(5, 0) << endl;
    cout << "Wartosc optymalna " << matrix.OPT << endl;

    matrix.brute_force_tsp();

    return 0;
}