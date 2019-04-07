//Babiienko I. K-11
#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>

class Greenhouse//клас Теплиця
{
public:
	Greenhouse();// constructor - gives initial values to all variables (that describe grrenhouse state)
	bool win_cl();// changes windows state to closed
	bool win_op();// changes windows state to open
	bool heat_on();// changes heaters state to on
	bool heat_off();// changes heaters state to off
	std::string state_output()const;//returns a string that describes system state
	void one_hour();//simulates changes in the system after one-hour functioning
	bool system_state_check()const;//checks if system is working
	int temp_current()const;//returns current value of temperature
	int hum_current()const;//returns current value of humidity
	bool win_state()const;//returns windows current state
	bool heat_state()const;//returns heaters current state
private:
	const int temp_max, temp_min, hum_max, hum_min;
	double temp, hum;
	bool win, heat;
};

#endif // MYCLASS_H


