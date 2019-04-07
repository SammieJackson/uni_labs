//BAbiienko, K-11
#include <iostream>
#include <string>
#include <sstream>
#include "Myclass.h"
#include "GetModel.h"
#include "Interface1.h"

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
	<< endl << " After that each hour you are asked to insert a command. List of valid commands follows:"
	<< endl << "   'OH' -- simulates a one hour pass;"
	<< endl << "   'WO' -- opens window;"
	<< endl << "   'WC' -- closes window;"
	<< endl << "   'HN' -- turns heater on;"
	<< endl << "   'HF' -- turns heater off;"
	<< endl << "   'GS' -- gives information about greenhouse current state;"
	<< endl << "   'FC' -- ends your control of the greenhouse. This command stops the program."
	<< endl << " Greenhouse may go out of service - if at least one of the conditions is too low or high."
	<< endl << " In case it happens, heater is automatically turned off and system state does not change."
	<< endl << " And only following commands will be available to you: GS and FC."
	<< endl << "-------------------------------------------------------------------------------------------------------------------";
	return;
}

void win_op_err_check(Greenhouse& greenhouse) {
	if (greenhouse.win_op() == 1) { cout << endl << " Window successfully opened."<<endl; }
	else { cout << endl << " Action impossible. Window is already open. Choose a valid command:"; };
	return;
}

void win_cl_err_check(Greenhouse& greenhouse) {
	if (greenhouse.win_cl() == 1) { cout << endl << " Window successfully closed."<<endl; }
	else { cout << endl << " Action impossible. Window is already closed. Choose a valid command:"; };
	return;
}

void heat_on_err_check(Greenhouse& greenhouse) {
	if (greenhouse.heat_on() == 1) { cout << endl << "Heater successfully turned on."<<endl; }
	else { cout << endl << "Action impossible. Heater is already on. Choose a valid command:"; };
	return;
}

void heat_of_err_check(Greenhouse& greenhouse) {
	if (greenhouse.heat_off() == 1) { cout << endl << "Heater successfully turned off."<<endl; }
	else { cout << endl << "Action impossible. Heater is already off. Choose a valid command:"; };
	return;
}

void do_comm_on(std::string &comm, Greenhouse& greenhouse) {
	if (comm == "OH") { greenhouse.one_hour(); cout<<endl<<greenhouse.state_output(); } else
    if (comm == "WO") { win_op_err_check(greenhouse);} else
	if (comm == "WC") { win_cl_err_check(greenhouse);} else
	if (comm == "HN") { heat_on_err_check(greenhouse);} else
	if (comm == "HF") { heat_of_err_check(greenhouse);} else
	if (comm == "GS") { cout<<endl<<greenhouse.state_output(); } else
	cout << endl << " Invalid input.";
	return;
}

void do_comm_of(std::string &comm, Greenhouse& greenhouse) {
    if ((comm == "OH") || (comm == "WO") || (comm == "WC") || (comm == "HN") || (comm == "HF")) { cout << endl << " This action is no more available. Please enter another command: "; } else
    if (comm == "GS") { cout<<endl<<greenhouse.state_output(); } else
	cout << endl << " Invalid input.";
	return;
}

void run_app() {
    Greenhouse* greenhouse = get_model();
    cout<<endl<<" Now, enter a valid command, please: ";
	std::string comm;
	cin >> comm;
    while ((greenhouse->system_state_check() == 1) && (comm != "FC")) {
        if (cin.eof()) {cout << endl << " Invalid input. Please enter a valid command: "; cin.clear(); cin.sync(); cin>>comm;} else {
          do_comm_on(comm, *greenhouse);
          cout << endl << " Enter a valid command: ";
          cin >> comm;}
    };
    if (comm == "FC") {cout<<endl<<" You finished running the greenhouse."; cout<<endl<<endl<<greenhouse->state_output()<<endl;}
    else {
     while (comm != "FC") {
        if (cin.eof()) {cout << endl << " Invalid input. Please enter a valid command: "; cin.clear(); cin.sync(); cin>>comm;} else {
		do_comm_of(comm, *greenhouse);
		cout << endl << " Enter a valid command: ";
		cin >> comm;}
	 };
	cout << endl << " You finished running the greenhouse."; cout<<endl<<endl<<greenhouse->state_output()<<endl;}
	delete greenhouse;
	return;
}
