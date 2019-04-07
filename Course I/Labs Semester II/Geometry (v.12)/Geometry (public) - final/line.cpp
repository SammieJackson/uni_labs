//Babiienko, K-11
#include "line.h"
#include <cmath>
#include <float.h>
#include <iostream>
#include "Tostring.h"

using std::string;
using namespace std;

bool isZero(double x){
	return fabs(x)<DBL_EPSILON;
}

Line::operator string() const{
    if (isValid()) return "("+to_string(a) + ")*x+("+to_string(b) + ")*y+("+ to_string(c)+")";
    else return "Not valid line";
}

void Line::write() const{
	cout<<operator string()<<endl;
}

Line::Line(double A,double B,double C):a(A), b(B), c(C){
    if (!isfinite(a) || !isfinite(b) ||!isfinite(c)) {a=b=c=0.;}
	normalize();
	check();
}

Line::Line(const Point&A, const Point&B){
	//some math, should be checked
	double dx=B.getX()-A.getX(), dy=B.getY()-A.getY();
	a=dy; b=-dx;c=dx*A.getY()-dy*A.getX();
	normalize();
	check();
}

bool Line::isValid()const{
	return (state);
}

bool Line::check(){
	state = (a!=0 || b!=0);
	return (state);
}

void Line::normalize(){
	if (b!=0) {	a/=b; c/=b; b=1;}
	else if (a!=0){c/=a;a=1;}
	else c=0;
}

bool Line::operator ==(const Line &line) const { //code is simplified due to normal form and invalid lines equality
	return (isZero(a-line.a) && isZero(b-line.b)&& isZero(c-line.c));
}

bool Line::contain(const Point &p) const {
	return isValid() && isZero(distanceSignedY(p));
}
bool Line::collinear(const Line &line) const{
	return (isValid() && line.isValid() && isZero(a-line.a) && isZero(b-line.b));
}

bool Line::parallel(const Line &line) const{
	return collinear(line) && !(operator==(line));
}

bool Line::perpendicular(const Line &line) const{
	return isValid() && line.isValid() && isZero(a*line.a+b*line.b);
}
bool Line::intersect(const Line &line) const{
	return isValid()&& line.isValid() && ! collinear(line);
}
Point Line::intersection(const Line &line) const{
if (!intersect(line)) return Point(0,0);
double det = a*line.b-line.a*b;
return Point(- (c*line.b-line.c*b)/det,- (a*line.c-line.a*c)/det);
}

double Line::distanceSignedY (const Point&p) const{
	return a*p.getX()+b*p.getY()+c;
}
double Line::distanceSigned (const Point&p) const{
	double d=distanceSignedY(p);
	if (a==0 || b==0) return d;
	return d*sqrt(a*a+1); // b==1 due to normalization
}
double Line::distance (const Point&p) const{
	return fabs(distanceSigned(p));
}
bool Line::otherSide (const Point &p1, const Point &p2)const{
	if (!isValid()) return false;
	double d1=distanceSignedY(p1), d2=distanceSignedY(p2);
	return (d1<0 && d2>0) || (d1>0 && d2<0);
}

bool Line::oneSide (const Point&p1, const Point&p2)const{
	if (!isValid()) return false;
	double d1=distanceSignedY(p1), d2=distanceSignedY(p2);
	return (d1<0 && d2<0) || (d1>0 && d2>0);
}
