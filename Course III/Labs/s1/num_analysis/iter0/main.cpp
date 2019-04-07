#include <iostream>
#include "pow.h"

using namespace std;


int main()
{
    test_simp();
    cout << endl;
    test_relax();
    cout << endl << endl << endl;
    test_cuts();
    cout << endl;
    return 0;
}
