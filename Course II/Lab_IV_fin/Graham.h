#ifndef GRAHAM_H_INCLUDED
#define GRAHAM_H_INCLUDED

#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>
#include "MyPoint.h"

using namespace std;


// A globle point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}


// A function used by library function qsort() to sort an array of
// points with respect to the first point
// -1 - if p1 is closer or more clockwise than p2
//  1 - if p2 is closer or more clockwise
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   int o;
   o = orientation_double(p0, *p1, *p2);
   ///o = orientation_int(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

// Finds convex hull of a set of n points.
void convexHull_G(vector<Point> points, vector<Point> & hull)
{
   int n = points.size();
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   swap(points[0], points[min]);

   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);

   int m = 1;
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation_double(p0, points[i], points[i+1]) == 0)
       //while (i < n-1 && orientation_int(p0, points[i], points[i+1]) == 0)
          i++;


       points[m] = points[i];
       m++;
   }

   if (m < 3) return;

   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i = 3; i < m; i++)
   {
      while (orientation_double(nextToTop(S), S.top(), points[i]) != 2)
      ///while (orientation_int(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }

   hull.resize(0);
   while (!S.empty())
   {
       Point p = S.top();
       hull.push_back(p);
       S.pop();
   }
}

// Driver program to test above functions
int mainG()
{
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<Point> hull_g;
    convexHull_G(points, hull_g);
    return 0;
}

#endif // GRAHAM_H_INCLUDED
