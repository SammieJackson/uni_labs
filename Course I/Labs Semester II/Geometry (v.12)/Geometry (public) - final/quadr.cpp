//Babiienko, K-11
#include <iostream>
#include "quadr.h"

using std::string;
using namespace std;

bool Quadri::input()
{
    for (int i=0; i<N; i++) {
        cout<<endl<<" Please, enter x and y coordinates (two finite real numbers) for point "<<name[i]<<" by separating them with space:";
        if (!vertex[i].read()) {
            details = "\n Sorry, you entered invalid coordinates.\n";
            return 0;
        }
    }
    return is_valid_check();
}

bool Quadri::is_valid_check()
{
    bool e=1;
    details = "\n OK - valid quadrilateral.\n";
    int i=0;
    while (e && (i<4)){
        int j=i+1;
        while (e && j<4){
            if (vertex[i] == vertex[j]) {
                details = "";
                details += "Invalid input: point ";
                details += name[i];
                details += " is coincident to point ";
                details += name[j];
                details += ".";
                e=0;
            }
            j++;
        }
        i++;
    }
    i=0;
    while (e && i<4){
        int j=i+1;
        while (e && j<4){
            int k=j+1;
            while (e && k<4){
                Line line(vertex[i],vertex[j]);
                if (line.contain(vertex[k])) {
                    details = "";
                    details += " Invalid input: points ";
                    details += name[i];
                    details += ", ";
                    details += name[j];
                    details += ", and ";
                    details += name[k];
                    details += " are collinear.";
                    e=0;
                }
                k++;
            }
            j++;
        }
        i++;
    }
    validity = e;
    return e;
}

Quadri::operator std::string()const{
    if (!validity) {return "\n Invalid quadrilateral.\n";} else {
    std::string oss = "\n ABCD quadrilateral: Edges: ";
    for (int i=0; i<N; i++){
        oss += name[i] + string(vertex[i]) + ", ";
    }
    oss += ".";
    return "\n"+oss+"\n";
  }
}

std::string Quadri::error_details()const{
    return "\n"+details+"\n";
}

bool Quadri::solve1(const Point& E)const{
    bool out=0;
    for (int i=0; i<N; i++){
            if (E == vertex[i]) out=1;
        }
    return out;
}

bool Quadri::solve2(const Point& E)const{
    bool out=0;
    Segment side[N];
    for (int i=0; i<N; i++){
        Segment seg(vertex[i],vertex[i+1]);
        side[i] = seg;
    }
        for (int i=0; i<N; i++) {
            if (side[i].contain_point(E)) out=1;
        }
    return out;
}

Point Quadri::find_line(const Point& E)const{
    Point O(0,0);
    int x=1, y=0;
    bool e=0;
    while (!e){
    Line myline(E,O);
    bool check=0;
    for (int i=0; i<N+2; i++){
        if (myline.contain(vertex[i])) check=1;
        }
        e = !check;
        Point A(x,y);
        O = A;
        y += x;
        ++x;
    }
    return O;
}

bool Quadri::solve3(const Point& E)const{
    Segment side[N];
    for (int i=0; i<N; i++){
        Segment seg(vertex[i],vertex[i+1]);
    side[i] = seg;
    }
    Point O = find_line(E);
    Line myline(E,O);
    int neg=0, k=0, j=0;
        while (j<N){
            Line line(vertex[j],vertex[j+1]);
            if (myline == line) k++; else
                if (side[j].intersects(myline)) {
                    Point Q=line.intersection(myline);
                    k++;
                    if ( ((Q.compareY(E)<0) && (E.compareY(O) != 0)) || ((E.compareY(O) == 0) && (Q.compareX(E)<0)) ) neg++;
                    }
                j++;
            }
    if ((k % 2 == 0) & (neg % 2 == 0)) return 0;
    return 1;
}

int Quadri::solve(const Point& E)const{
    if (validity) {
        if (solve1(E)) return 0;
        if (solve2(E)) return 2;
        if (solve3(E)) return 1;
        return -1;
    }
    return -2;
}

std::string Quadri::interpret_results(const Point& E)const{
    int i = solve(E);
    if (i == 0) return "\n Inspected point lies in the vertex of given quadrilateral.\n";
    if (i == 2) return "\n Inspected point lies on the edge of given quadrilateral. \n";
    if (i == 1) return "\n Inspected point lies inside the given quadrilateral.\n";
    if (i == -1) return "\n Inspected point lies outside the given quadrilateral.\n";
    if (i == -2) return "\n Program could not be executed. Invalid quadrilateral.";
    return "\n FATAL ERROR!\n";
}
