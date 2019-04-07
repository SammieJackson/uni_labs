//Babiienko, K-11
#include <iostream>
#include "Interface2.h"
#include "Myclass.h"

using namespace std;

void instruct() {

	cout << endl << " This program has been created by Illia Babiienko, K-11.";
	cout << endl << " It simulates greenhouse functioning process. Greenhouse has a window and a heater (levelers to operate the greenhouse).";
	cout << endl << " Window can either be opened or closed. Heater - on or off.";
	cout << endl << " Greenhouse state is described by temperature and humidity (conditions). Initially, they are 25 and 60 respectively.";
	cout << endl << " Depending on state of levelers, conditions change each day. You are the greenhouse owner.";
	cout << endl << " Greenhouse may go out of service - if at least one of the conditions is too low or high: 10<=temp<=45, and 45<=hum<=75.";
	cout << endl << " In case it happens, heater is automatically turned off and system state does not change. You will be notified.";
	cout << endl << " Greenhouse is operated automatically. Program outputs system state after each time unit (one day) passes.";
	cout << endl << "-------------------------------------------------------------------------------------------------------------------";
	return;
}

void run_app() {
	int day = 0;
	Greenhouse gh;
	cout << " Day 0 (default state):"<<endl<<gh.state_output()<<endl<<endl;
	while (gh.system_state_check()== 1) {
		day++;
		gh.one_hour();
		cout << endl << " Day " << day << ":" << endl;
		cout << gh.state_output();
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << endl << " System went out of service. It has successfully worked for " << day << " days.";
	cout << endl << " Last day: " << gh.state_output()<<endl<<"------------------------------------------------------------------------------------";
}
