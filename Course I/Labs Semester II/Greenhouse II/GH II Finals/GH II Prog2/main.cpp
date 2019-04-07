//Babiienko, K-11
#include <iostream>
#include "Interface2.h"
#include "copy.h"

using namespace std;

int main()
{
    copyright();
	instruct();
	try{
	run_app();
	}
	catch (const bad_alloc &ex){cout<<endl<<" We're sorry, something went wrong. We are working on it. Try again later.";}
	return 0;
}
