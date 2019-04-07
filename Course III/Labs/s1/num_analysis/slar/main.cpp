#include <iostream>
#include "methods.h"
#include "tests.h"

using namespace std;
using namespace Eigen;

void tests()
{
    ///test_eigen_core();
    ///test_print();
    ///test_G_dir_step_arg_pass();
    ///test_emax();
    ///test_gauss_steps();

    ///test_Yarik();
}

int main()
{
    ///tests();
    ///part_I_everything();
    part_II();

    /**
    db e1 = 1e-2, e2=1e-02;
    cout << "\n\n" << std::fixed;
    cout << " " << e1 << " " << e2;
    cout << "\n\n" << std::scientific;
    cout << " " << e1 << " " << e2;
    //**/

    return 0;
}
