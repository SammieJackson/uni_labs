//Babiienko I. K-11
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Myclass.h"

using std::string;
using namespace std;


bool Greenhouse::win_cl() { if (win_state()) {win = 0; return 1;} else {return 0;}}

bool Greenhouse::win_op() { if (!win_state()) {win = 1; return 1;} else {return 0;}}

bool Greenhouse::heat_off() { if (heat_state()) {heat = 0; return 1;} else {return 0;}}

bool Greenhouse::heat_on() { if (!heat_state()) {heat = 1; return 1;} else {return 0;}}

int Greenhouse::temp_current()const { return temp; }

int Greenhouse::hum_current()const { return hum; }

bool Greenhouse::win_state()const { return win; }

bool Greenhouse::heat_state()const { return heat; }

bool Greenhouse::system_state_check() const{
	if ((temp <= temp_max()) && (temp >= temp_min()) && (hum >= hum_min()) && (hum <= hum_max())) { return 1; }
	else { return 0; }
}

std::string Greenhouse::state_output()const {
 std::ostringstream oss;
 oss << " Greenhouse type - " << type_out() << " state:\n system - ";
	if (system_state_check()) { oss << "working;"; }
	else { oss << "out of service;"; };
	oss << " window - ";
	if (win_state()) { oss << "open;"; }
	else { oss << "closed;"; };
	oss << " heat - ";
	if (heat_state()) { oss << "on;"; }
	else { oss << "off;"; }
	oss << endl;
	oss << " current temperature = "; oss << fixed << /*setprecision(2) <<*/ temp_current();
	oss << "; current humidity = "; oss << fixed << /*setprecision(4) <<*/ hum_current(); oss << ".\n";
	return oss.str();
}

std::string Greenhouse::type_out()const{return "";}

void Greenhouse::one_hour() {
	if ((!win_state()) && (!heat_state())) { temp += t00(); hum += h00(); };
	if ((win_state()) && (!heat_state())) { temp += t10(); hum += h10(); };
	if ((!win_state()) && (heat_state())) { temp += t01(); hum += h01(); };
	if ((win_state()) && (heat_state())) { temp += t11(); hum += h11(); };
	return;
}

bool Greenhouse::win_init()const{return 0;}

bool Greenhouse::heat_init()const{return 0;}

int Greenhouse::temp_init()const{return 0;}

int Greenhouse::hum_init()const{return 0;}

int Greenhouse::temp_max()const{return 0;}

int Greenhouse::temp_min()const{return 0;}

int Greenhouse::hum_max()const{return 0;}

int Greenhouse::hum_min()const{return 0;}

double Greenhouse::t00()const{return 0;}

double Greenhouse::h00()const{return 0;}

double Greenhouse::t01()const{return 0;}

double Greenhouse::h01()const{return 0;}

double Greenhouse::t10()const{return 0;}

double Greenhouse::h10()const{return 0;}

double Greenhouse::t11()const{return 0;}

double Greenhouse::h11()const{return 0;}



GHtype1::GHtype1()
{
    temp=temp_init();
    hum=hum_init();
    win=win_init();
    heat=heat_init();
}

int GHtype1::temp_init()const{
return 20;
}

int GHtype1::hum_init()const{
return 60;
}

int GHtype1::temp_max()const{
return 35;
}

int GHtype1::temp_min()const{
return 5;
}

int GHtype1::hum_max()const{
return 75;
}

int GHtype1::hum_min()const{
return 45;
}

double GHtype1::t00()const{
return -1;
}

double GHtype1::h00()const{
return -1;
}

double GHtype1::t01()const{
return 2;
}

double GHtype1::h01()const{
return 2;
}

double GHtype1::t10()const{
return -2;
}

double GHtype1::h10()const{
return -2;
}

double GHtype1::t11()const{
return 1;
}

double GHtype1::h11()const{
return 1;
}

std::string GHtype1::type_out()const{
    std::ostringstream out;
    out << "GHI(this is a 1st type greenhouse - for ordinary conditions)";
    return out.str();
}

GHtype2::GHtype2()
{
    temp=temp_init();
    hum=hum_init();
    win=win_init();
    heat=heat_init();
}

int GHtype2::temp_init()const{
return 20;
}

int GHtype2::hum_init()const{
return 65;
}

int GHtype2::temp_max()const{
return 40;
}

int GHtype2::temp_min()const{
return 10;
}

int GHtype2::hum_max()const{
return 85;
}

int GHtype2::hum_min()const{
return 40;
}

double GHtype2::t00()const{
return -1;
}

double GHtype2::h00()const{
return -1;
}

double GHtype2::t01()const{
return 4;
}

double GHtype2::h01()const{
return 4;
}

double GHtype2::t10()const{
return -2;
}

double GHtype2::h10()const{
return -2;
}

double GHtype2::t11()const{
return 2;
}

double GHtype2::h11()const{
return 1;
}

std::string GHtype2::type_out()const{
    std::ostringstream out;
    out << "GHII(this is 2nd type greenhouse - for tropical plants with powerful heater)";
    return out.str();
}

GHtype3::GHtype3()
{
    temp=temp_init();
    hum=hum_init();
    win=win_init();
    heat=heat_init();
}

int GHtype3::temp_init()const{
return 15;
}

int GHtype3::hum_init()const{
return 60;
}

int GHtype3::temp_max()const{
return 25;
}

int GHtype3::temp_min()const{
return -5;
}

int GHtype3::hum_max()const{
return 90;
}

int GHtype3::hum_min()const{
return 30;
}

double GHtype3::t00()const{
return -1;
}

double GHtype3::h00()const{
return -1;
}

double GHtype3::t01()const{
return 1;
}

double GHtype3::h01()const{
return 1;
}

double GHtype3::t10()const{
return -2;
}

double GHtype3::h10()const{
return -2;
}

double GHtype3::t11()const{
return 0.5;
}

double GHtype3::h11()const{
return 0.5;
}

std::string GHtype3::type_out()const{
    std::ostringstream out;
    out << "GHIII(this is 3rd type greenhouse - for cold-resistant plants with more economical heater)";
    return out.str();
}
