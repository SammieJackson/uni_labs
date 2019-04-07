//Babiienko I. K-11
#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>

class Greenhouse
{
public:
	bool win_cl();// changes windows state to closed
	bool win_op();// changes windows state to open
	bool heat_on();// changes heaters state to on
	bool heat_off();// changes heaters state to off
	std::string state_output()const;//returns a string that describes system state
	virtual std::string type_out()const;//returns type of greenhouse
	void one_hour();//simulates changes in the system after one-hour functioning
	bool system_state_check()const;//checks if system is working
	int temp_current()const;//returns current value of temperature
	int hum_current()const;//returns current value of humidity
	bool win_state()const;//returns windows current state
	bool heat_state()const;//returns heaters current state
	virtual ~Greenhouse()=default;
protected:
    bool win_init()const;
    bool heat_init()const;
    virtual int temp_init()const;
    virtual int hum_init()const;
	virtual int temp_max()const;
	virtual int temp_min()const;
	virtual int hum_max()const;
	virtual int hum_min()const;
	virtual double t00()const;
	virtual double h00()const;
	virtual double t01()const;
	virtual double h01()const;
	virtual double t10()const;
	virtual double h10()const;
	virtual double t11()const;
	virtual double h11()const;
	double temp, hum;
	bool win, heat;
};

class GHtype1:public Greenhouse
{
public:
    GHtype1();//initializes all constant variables
    std::string type_out()const;
private:
    int temp_init()const;
    int hum_init()const;
    int temp_max()const;
	int temp_min()const;
	int hum_max()const;
	int hum_min()const;
	double t00()const;
	double h00()const;
	double t01()const;
	double h01()const;
	double t10()const;
	double h10()const;
	double t11()const;
	double h11()const;
};

class GHtype2:public Greenhouse
{
public:
    GHtype2();
    std::string type_out()const;
private:
    int temp_init()const;
    int hum_init()const;
    int temp_max()const;
	int temp_min()const;
	int hum_max()const;
	int hum_min()const;
	double t00()const;
	double h00()const;
	double t01()const;
	double h01()const;
	double t10()const;
	double h10()const;
	double t11()const;
	double h11()const;
};

class GHtype3:public Greenhouse
{
public:
    GHtype3();
    std::string type_out()const;
private:
    int temp_init()const;
    int hum_init()const;
    int temp_max()const;
	int temp_min()const;
	int hum_max()const;
	int hum_min()const;
	double t00()const;
	double h00()const;
	double t01()const;
	double h01()const;
	double t10()const;
	double h10()const;
	double t11()const;
	double h11()const;
};

#endif // MYCLASS_H

