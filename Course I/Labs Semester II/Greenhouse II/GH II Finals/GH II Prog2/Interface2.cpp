//Babiienko, K-11
#include <iostream>
#include <string>
#include <sstream>
#include "Myclass.h"
#include "GetModel.h"
#include "Interface2.h"

using std::string;
using namespace std;

void instruct() {
	cout << endl << " This program has been created by Illia Babiienko, K-11."
	<< endl << " It simulates greenhouse functioning process. Greenhouse has a window and a heater (levelers to operate the greenhouse)."
	<< endl << " Window can either be opened or closed. Heater - on or off."
	<< endl << " Greenhouse state is described by temperature and humidity (conditions)."
	<< endl << " Depending on state of levelers, conditions change each hour. You are the greenhouse owner."
	<< endl << " There are three types of greenhouses. They have different condition limit values and change rates."
	<< endl << " First you are asked to select the type of your greenhouse: 1, 2 or 3. You have to enter respective integer. "
	<< endl << " Greenhouse may go out of service - if at least one of the conditions is too low or high."
	<< endl << " In case it happens, heater is automatically turned off and system state does not change."
    << endl << " Greenhouse is operated automatically. Program outputs system state after each time unit (one day) passes."
	<< endl << "-------------------------------------------------------------------------------------------------------------------";
	return;
}

void run_app(){
    Greenhouse* gh = get_model();
    int day = 0;
	cout << " Day 0 (default state):"<<endl<<gh->state_output()<<endl<<endl;
	while (gh->system_state_check()== 1) {
		day++;
		gh->one_hour();
		cout << endl << " Day " << day << ":" << endl;
		cout << gh->state_output();
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << endl << " System went out of service. It has successfully worked for " << day << " days." << endl;
	cout << endl << " Last day: " << gh->state_output()<<endl<<"------------------------------------------------------------------------------------";
	delete gh;
	return;
}
