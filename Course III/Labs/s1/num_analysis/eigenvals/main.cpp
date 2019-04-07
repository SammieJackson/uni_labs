#include <iostream>
#include "methods.h"
#include "tests.h"

using namespace std;

void tests_all()
{
    ///test_transpose();
    ///test_dot_product();

    ///test_power_method();
    test_jacobi_method();
}

int main()
{
    tests_all();
    return 0;
}
