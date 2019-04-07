#include "GetModel.h"
#include <iostream>

using namespace std;

Greenhouse* get_model() {
    cout << endl << " Now, select the greenhouse type, please: ";
    int type;
    Greenhouse *greenhouse = nullptr;
    cin>>type;
    while (cin.fail() || (type>3) || (type<1)){
        cout<<endl<<" Invalid input. Enter an integer between 1 and 3 (1 or 2 or 3):";
        cin.clear(); cin.sync(); cin>>type;
    };
    if (type == 1) {greenhouse = new GHtype1;} else
    if (type == 2) {greenhouse = new GHtype2;} else
    if (type == 3) {greenhouse = new GHtype3;};
	return greenhouse;
}
