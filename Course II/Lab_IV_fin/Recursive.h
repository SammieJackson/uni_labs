#ifndef RECURSIVE_H_INCLUDED
#define RECURSIVE_H_INCLUDED

#include "MyPoint.h"
#include <vector>
#include <algorithm>

using namespace std;

double triangle_area (const Point& p1, const Point& p2, const Point& p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void find_hull(const Point& start, const Point& fin, vector<Point> points, vector<Point> & hull)
{
    int n = points.size();
    if (n == 0) {
        hull.push_back(start);
        return;
    }
    if (n == 1) {
        hull.push_back(start);
        hull.push_back(points[0]);
        return;
    }
    double max_area = 0;
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        double area = triangle_area(start, fin, points[i]);
        if (area > max_area || (area == max_area && distSq(start, points[i]) < distSq(start, points[index])) )
        {
            max_area = area;
            index = i;
        }
    }
    vector<Point> first_set, second_set;
    for (int i = 0; i < n; ++i)
    {
        if (i != index)
        {
            if ( orientation_double(start, points[index], points[i]) == 2) first_set.push_back(points[i]);
            if ( orientation_double(fin, points[index], points[i]) == 1) second_set.push_back(points[i]);
            ///if ( orientation_int(start, points[index], points[i]) == 2) first_set.push_back(points[i]);
            ///if ( orientation_int(fin, points[index], points[i]) == 1) second_set.push_back(points[i]);
        }
    }
    find_hull(start, points[index], first_set, hull);
    find_hull(points[index], fin, second_set, hull);

}

void convexHull_R(vector<Point> points, vector<Point> & hull)
{
    int n = points.size();
    if (n < 3) return;
    vector <Point> p = points;
    sort(p.begin(), p.end(), &cmp_x_y);
    Point start = p[0], finn = p.back();
    hull.resize(0);
    vector<Point> first_set, second_set;
    for (int i = 0; i < n; ++i)
    {
        int orient = orientation_double(start, finn, points[i]);
        ///int orient = orientation_int(start, finn, points[i]);
        if (orient == 2) first_set.push_back(points[i]);
        if (orient == 1) second_set.push_back(points[i]);
    }
    find_hull(start, finn, first_set, hull);
    find_hull(finn, start, second_set, hull);
}


#endif // RECURSIVE_H_INCLUDED
