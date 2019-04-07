//Babiienko I. K-11
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include "Myclass.h"

using std::string;
using namespace std;

Greenhouse::Greenhouse() : temp(20), hum(60), temp_max(35), temp_min(5), hum_max(75), hum_min(45), win(0), heat(0)
{
}

bool Greenhouse::win_cl() { if (win_state()) {win = 0; return 1;} else {return 0;}}

bool Greenhouse::win_op() { if (!win_state()) {win = 1; return 1;} else {return 0;}}

bool Greenhouse::heat_off() { if (heat_state()) {heat = 0; return 1;} else {return 0;}}

bool Greenhouse::heat_on() { if (!heat_state()) {heat = 1; return 1;} else {return 0;}}

int Greenhouse::temp_current()const { return temp; }

int Greenhouse::hum_current()const { return hum; }

bool Greenhouse::win_state()const { return win; }

bool Greenhouse::heat_state()const { return heat; }

bool Greenhouse::system_state_check() const{
	if ((temp <= temp_max) && (temp >= temp_min) && (hum >= hum_min) && (hum <= hum_max)) { return 1; }
	else { return 0; }
}

std::string Greenhouse::state_output()const {
 std::ostringstream oss;
 oss << " Greenhouse state: system - ";
	if (system_state_check() == 1) { oss << "working;"; }
	else { oss << "out of service;"; };
	oss << " window - ";
	if (win_state() == 1) { oss << "open;"; }
	else { oss << "closed;"; };
	oss << " heat - ";
	if (heat_state() == 1) { oss << "on;"; }
	else { oss << "off;"; }
	oss << endl;
	oss << " current temperature = "; oss << fixed << /*setprecision(2) <<*/ temp_current();
	oss << "; current humidity = "; oss << fixed << /*setprecision(4) <<*/ hum_current(); oss << ".";
	oss<<endl<<"--------------------------------------------------------------------------------------";
	return oss.str();
}

void Greenhouse::one_hour() {
	if ((!win_state()) && (!heat_state())) { temp += -1; hum += -1; };
	if ((win_state()) && (!heat_state())) { temp += -2; hum += -2; };
	if ((!win_state()) && (heat_state())) { temp += 2; hum += 2; };
	if ((win_state()) && (heat_state())) { temp += 1; hum += 1; };
	return;
}
