//Babiienko, K-11
#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include "point.h"

class Point;
class Line{
public:
	Line(double A=0,double B=0,double C=0); // for not finite A, B, C set them to 0 0 0
	Line(const Point&, const Point&);
	void write() const; // as ax+by+c=0
	operator std::string() const; // as ax+by+c=0
	bool isValid() const;
	bool operator == (const Line&) const;// assume that invalid lines are equal; here and then DBL_EPSILON accuracy
	bool contain(const Point&) const;
	bool collinear(const Line &) const;
	bool parallel(const Line &) const;
	bool perpendicular(const Line &) const;
	bool intersect(const Line &) const; // чи перетинаються (але не співпадають)
	Point intersection(const Line &) const;// return intersection point if exactly one exist, else return (0,0)
	bool otherSide (const Point&, const Point&)const;// чи по різні боки
	bool oneSide (const Point&, const Point&)const;// чи по один бік
	double distanceSigned(const Point&)const; // for invalid line return 0
	double distance(const Point&)const;		  // for invalid line return 0
private:
    double a,b,c;     //ax+by+c=0
	bool state;       // true iff we have line
	void normalize(); //if a,b !=0 then b=1; if b=0, a!=0 then a=1; if a,b==0 then c=0
	bool check();     //set and return state
    double distanceSignedY(const Point&)const;// for invalid line return 0
};

#endif // LINE_H_INCLUDED
