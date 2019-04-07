//Babiienko, K-11
#include <iostream>
#include "interface.h"
#include "quadr.h"

using namespace std;

void instruct(){
    cout<<endl<<" This program determines whether point E lies inside, outside or on the side of ABCD quadrangle.";
    cout<<endl<<" Coordinates for all five points (A, B, C, D, and E) are finite real numbers and entered by the user.";
    cout<<endl<<" If input is invalid (entered values are not numbers or some three points of A, B, C, and D lie on single line) program shuts down and prints corresponding message."<<endl;
return;
}

void run_app(){
    instruct();
    Quadri quadr;
    int valid=quadr.input();
    if (valid) {
        cout<<endl<<" Please, enter x and y coordinates (two finite real numbers) for point E by separating them with space:";
        Point E(0,0);
        if (!E.read()) {
            cout<<endl<<" Sorry, you entered invalid coordinates."<<endl;
        } else {
        cout<<endl<<" You entered the following quadrilateral:"<<string(quadr)<<endl<<" And following coordinates for point E: "<<string(E)<<endl<<quadr.interpret_results(E);
        }
    }
    else {
        cout<<quadr.error_details();
    }
    return;
}
