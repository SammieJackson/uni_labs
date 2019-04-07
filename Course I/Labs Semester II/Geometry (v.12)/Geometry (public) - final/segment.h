//Babiienko, K-11
#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED
#include "line.h"

class Segment{
public:
    Segment();
    Segment(const Point&, const Point&);
    bool betweenX(const Point&)const;//�������� �� ������ ����� ������ �� ����� �� �� � � � �� ��������� � (���� ���� �� ���)
    bool betweenY(const Point&)const;//�������� �� ������ ����� ������ �� ����� �� �� � � � �� ��������� � (���� ���� �� ���)
    bool contain_point(const Point&)const;
    bool intersects(const Line&)const;
    operator =(const Segment&);
private:
    Point A, B;
};

#endif // SEGMENT_H_INCLUDED
