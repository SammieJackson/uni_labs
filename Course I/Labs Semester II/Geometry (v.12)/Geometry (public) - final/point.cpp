//Babiienko, K-11
#include "point.h"
#include <iostream>
#include <istream>
#include <cmath>
#include "Tostring.h"

using std::string;
using namespace std;

Point::Point(double x1,double y1){ set(x1,y1);}

bool Point::set(double x1,double y1){
    if (!isfinite(x1) || !isfinite(y1)) { x=y=0.; return false;}
    else {x=x1; y=y1; return true;}
}

bool Point::read(){
    double x1,y1;
	if (!(cin>>x1>>y1)) {cin.clear(); cin.sync(); return false;}
	return set(x1,y1);
}

Point::operator string() const{
    return "("+to_string(x)+", "+to_string(y) +")";
}

void Point::write()const {
	cout<<operator string();
}
double Point::getX() const {return x;}
double Point::getY() const {return y;}

bool Point::operator ==(const Point& other)const{
return (x==other.x)&&(y==other.y);
}
bool Point::operator >(const Point& other)const{
return (x>other.x)||((x==other.x)&&(y>other.y));
}
bool Point::operator <(const Point& other)const{
return (x<other.x)||((x==other.x)&&(y<other.y));
}
bool Point::operator >=(const Point& other)const{
return operator==(other) || operator>(other); // to avoid code duplication
}
bool Point::operator <=(const Point& other)const{
return operator==(other) || operator<(other); // to avoid code duplication
}

const Point& Point::operator ||(const Point&other) const{
if (operator>=(other)) return *this; else return other;
}
const Point& Point::operator &&(const Point&other) const{
if (operator<=(other)) return *this; else return other;
}
double Point::compareX(const Point& other) const {return x-other.x;}
double Point::compareY(const Point& other) const {return y-other.y;}
double dist(const Point&a, const Point&b){
	double dx=a.getX()-b.getX(), dy=a.getY()-b.getY();
	return sqrt(dx*dx+dy*dy);}
