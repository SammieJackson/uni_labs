#ifndef KIRPATRICK_H_INCLUDED
#define KIRPATRICK_H_INCLUDED

#include "MyPoint.h"
#include <vector>
#include <algorithm>

using namespace std;

bool compare_y_x(const Point& p1, const Point& p2)
{
    return (  (p1.y < p2.y) || ((p1.y == p2.y)  && (p1.x < p2.x)) );
}



void convexHull_K ( vector<Point> points, vector<Point> & hull )
{
    int n = points.size();
    if (n < 3) return;
    sort(points.begin(), points.end(), &compare_y_x);

    vector<Point> left_points, right_points;
    int i = 0;
    while (i < n)
    {
        left_points.emplace_back(points[i]);
        while(points[i].y == points[i+1].y && i < n) ++i;
        right_points.emplace_back(points[i]);
        ++i;
    }

    hull.resize(0);
    int ls = left_points.size(), rs = right_points.size();
    vector<Point> left_hull, right_hull;
    left_hull.push_back(left_points[0]);
    left_hull.push_back(left_points[1]);
    right_hull.push_back(right_points[0]);
    right_hull.push_back(right_points[1]);
    i = 2;
    while (i < ls)
    {
        while( orientation_double(left_hull[left_hull.size() - 2], left_hull[left_hull.size() - 1], left_points[i]) == 2 && left_hull.size() > 1 )
        ///while( orientation_int(left_hull[left_hull.size() - 2], left_hull[left_hull.size() - 1], left_points[i]) == 2  )
        ///while( counterclockwise(left_hull[left_hull.size() - 2], left_hull[left_hull.size() - 1], left_points[i]) )
            left_hull.pop_back();
        left_hull.push_back(left_points[i]);
        ++i;
    }
    i = 2;
    while (i < rs)
    {
        while( orientation_double(right_hull[right_hull.size() - 2], right_hull[right_hull.size() - 1], right_points[i]) == 1 && right_hull.size() > 1 )
        ///while( orientation_int(right_hull[right_hull.size() - 2], right_hull[right_hull.size() - 1], right_points[i]) == 1  )
        ///while( clockwise(right_hull[right_hull.size() - 2], right_hull[right_hull.size() - 1], right_points[i])  )
            right_hull.pop_back();
        right_hull.push_back(right_points[i]);
        ++i;
    }

    ls = left_hull.size();
    rs = right_hull.size();
    i = 0;
    while (i < ls)
    {
        hull.emplace_back(left_hull[i]);
        ++i;
    }
    i = 1;
    while (i <= rs)
    {
        hull.emplace_back(right_hull[rs - i]);
        ++i;
    }

}

#endif // KIRPATRICK_H_INCLUDED
