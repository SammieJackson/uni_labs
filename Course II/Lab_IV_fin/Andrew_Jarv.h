#ifndef ANDREW_JARV_H_INCLUDED
#define ANDREW_JARV_H_INCLUDED

#include <algorithm>
#include "MyPoint.h"


void convexHull_AJ (vector<Point> & a, vector<Point> & hull) {
	if (a.size() == 1)  return;
	sort (a.begin(), a.end(), &cmp_x_y);
	Point p1 = a[0],  p2 = a.back();
	vector<Point> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i=1; i<a.size(); ++i) {
		if (i==a.size()-1 || clockwise (p1, a[i], p2)) {
			while (up.size()>=2 && !clockwise (up[up.size()-2], up[up.size()-1], a[i]))
				up.pop_back();
			up.push_back (a[i]);
		}
		if (i==a.size()-1 || counterclockwise (p1, a[i], p2)) {
			while (down.size()>=2 && !counterclockwise (down[down.size()-2], down[down.size()-1], a[i]))
				down.pop_back();
			down.push_back (a[i]);
		}
	}
	//a.clear();
	hull.resize(0);
	for (size_t i=0; i<up.size(); ++i)
		hull.push_back (up[i]);
	for (size_t i=down.size()-2; i>0; --i)
		hull.push_back (down[i]);
}


#endif // ANDREW_JARV_H_INCLUDED
