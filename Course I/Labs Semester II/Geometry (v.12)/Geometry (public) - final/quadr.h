//Babiienko, K-11
#ifndef QUADR_H_INCLUDED
#define QUADR_H_INCLUDED
#include "segment.h"

class Quadri{
public:
    bool input();
    bool is_valid_check();//�������� ���������� ��������� �������������
    bool solve1(const Point&)const;//�������� �� ������� ������ ����� � ������ � ������
    bool solve2(const Point&)const;//�������� �� ������ ������ ����� �� ����� � ����� (� �� � ������)
    bool solve3(const Point&)const;//�������� �� ������ ����� ������ �������� �� �����
    int solve(const Point&)const;// ����'��� ������ - ����� 0 ��� �������, 2 ��� �������, 1 ��� ��������, -1 ��� �����, -2 ��� ����������� �������������
    operator std::string() const;
    Point find_line(const Point&)const;//��� ������ ����� ��������� �����, �� �� ��������� ����� ����� � ������ ������������� (������� ����� �� ��� �����)
    std::string error_details()const;//�������� ����������� ��� ������� (� ����������)
    std::string interpret_results(const Point&)const;//���� ����������� ��� ������� ��������� ����'���� ������
private:
    std::string details;
    bool validity;
    static const int N=4;
    const char name[N]={'A','B','C','D'};
    Point vertex[N+1];
};

#endif // QUADR_H_INCLUDED
