//Babiienko, K-11
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <string>

class Point{
private: double x,y;
public: Point(double x1=0, double y1=0); //for not finite x1, y1 set both them to 0
        bool set(double x1, double y1);//for not finite x1, y1 set both them to 0
        bool read();  //true iff OK
		void write() const;
		operator std::string() const;
		double getX() const;
		double getY() const;
		double compareX(const Point&) const; // <0 якщо менша по x; >0 якщо більша по x; 0 якщо x-координати однакові
		double compareY(const Point&) const; // аналогічно попередньому, але по y
		bool operator ==(const Point&) const;
		bool operator >(const Point&) const; //lexicographically
		bool operator <(const Point&) const;
		bool operator >=(const Point&) const;
		bool operator <=(const Point&) const;
		const Point& operator ||(const Point&) const; // max
		const Point& operator &&(const Point&) const; // min
 };

double dist(const Point&, const Point&);

#endif // POINT_H_INCLUDED
