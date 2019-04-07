//BAbiienko, K-11
#include <iostream>
#include <string>
#include "Myclass.h"
#include "Interface1.h"

using std::string;
using namespace std;

void instruct() {
	cout << endl << " This program has been created by Illia Babiienko, K-11.";
	cout << endl << " It simulates greenhouse functioning process. Greenhouse has a window and a heater (levelers to operate the greenhouse).";
	cout << endl << " Window can either be opened or closed. Heater - on or off.";
	cout << endl << " Greenhouse state is described by temperature and humidity (conditions). Initially, they are 20 and 60 respectively.";
	cout << endl << " Depending on state of levelers, conditions change each hour. You are the greenhouse owner.";
	cout << endl << " Each hour you are asked to insert a command. List of valid commands follows:";
	cout << endl << "   'OH' -- simulates a one hour pass;";
	cout << endl << "   'WO' -- opens window;";
	cout << endl << "   'WC' -- closes window;";
	cout << endl << "   'HN' -- turns heater on;";
	cout << endl << "   'HF' -- turns heater off;";
	cout << endl << "   'GS' -- gives information about greenhouse current state;";
	cout << endl << "   'FC' -- ends your control of the greenhouse. This command stops the program.";
	cout << endl << " Greenhouse may go out of service - if at least one of the conditions is too low or high: 5<=temp<=35, and 45<=hum<=75.";
	cout << endl << " In case it happens, heater is automatically turned off and system state does not change.";
	cout << endl << " And only following commands will be available to you: GS and FC.";
	cout << endl << "-------------------------------------------------------------------------------------------------------------------";
	cout << endl << " Now, enter a valid command, please: ";
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
	if (comm== "OH") { greenhouse.one_hour(); cout<<endl<<greenhouse.state_output(); } else
    if (comm== "WO") { win_op_err_check(greenhouse);} else
	if (comm== "WC") { win_cl_err_check(greenhouse);} else
	if (comm== "HN") { heat_on_err_check(greenhouse);} else
	if (comm== "HF") { heat_of_err_check(greenhouse);} else
	if (comm== "GS") { cout<<endl<<endl<<greenhouse.state_output()<<endl; } else
	cout << endl << " Invalid input.";
	return;
}

void do_comm_of(std::string &comm, Greenhouse& greenhouse) {
    if ((comm == "OH") || (comm == "WO") || (comm == "WC") || (comm == "HN") || (comm == "HF")) { cout << endl << " This action is no more available. Please enter another command: "; } else
    if (comm == "GS") { cout<<endl<<endl<<greenhouse.state_output()<<endl; } else
	cout << endl << " Invalid input.";
	return;
}

void run_app0(Greenhouse& greenhouse) {
	std::string comm;
	cin >> comm;
    while ((greenhouse.system_state_check ()== 1) && (comm != "FC")) {
        if (cin.eof()) {cout << endl << " Invalid input. Please enter a valid command: "; cin.clear(); cin.sync(); cin>>comm;} else {
          do_comm_on(comm, greenhouse);
          cout << endl << " Enter a valid command: ";
          cin >> comm;}
    };
    if (comm == "FC") {cout<<endl<<" You finished running the greenhouse."; cout<<endl<<endl<<greenhouse.state_output()<<endl; return;}
    else {
     while (comm != "FC") {
        if (cin.eof()) {cout << endl << " Invalid input. Please enter a valid command: "; cin.clear(); cin.sync(); cin>>comm;} else {
		do_comm_of(comm, greenhouse);
		cout << endl << " Enter a valid command: ";
		cin >> comm;}
	 };
	cout << endl << " You finished running the greenhouse."; cout<<endl<<endl<<greenhouse.state_output()<<endl; return;}
}

void run_app(){
Greenhouse greenhouse;
run_app0(greenhouse);
}
