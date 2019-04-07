//Babiienko, K-11
#include "segment.h"

using std::string;
using namespace std;

Segment::Segment(){
Point X(0,0), Y(0,0);
A=X;
B=Y;
}

Segment::Segment(const Point& A0, const Point& B0)
{
    A = A0;
    B = B0;
}

bool Segment::betweenX(const Point& O)const{
    Line line(A,B);
    return (line.contain(O) && ( ( (A.compareX(O)>0) && (B.compareX(O)<0) && (A.compareX(B)>0) ) || ( (A.compareX(O)<0) && (B.compareX(O)>0) && (A.compareX(B)<0)) ));
}

bool Segment::betweenY(const Point& O)const{
    Line line(A,B);
    return (line.contain(O) && ( ( (A.compareY(O)>0) && (B.compareY(O)<0) && (A.compareY(B)>0) ) || ( (A.compareY(O)<0) && (B.compareY(O)>0) && (A.compareY(B)<0)) ));
}

bool Segment::contain_point(const Point& O)const{
    if (A.compareX(B) != 0)  return betweenX(O);
    return betweenY(O);
}

bool Segment::intersects(const Line& line)const{
    return line.otherSide(A, B);
}

Segment::operator =(const Segment& other){
    A=other.A;
    B=other.B;
    return true;
}
