//Babiienko, K-11
#ifndef QUADR_H_INCLUDED
#define QUADR_H_INCLUDED
#include "segment.h"

class Quadri{
public:
    bool input();
    bool is_valid_check();//перевіряє коректінсть введеного чотирикутника
    bool solve1(const Point&)const;//перевіряє чи співпадає задана точка з якоюсь з вершин
    bool solve2(const Point&)const;//перевіряє чи лежить задана точка на якійсь зі сторін (і не в вершині)
    bool solve3(const Point&)const;//перевіряє чи задана точка лежить всередині чи ззовні
    int solve(const Point&)const;// розв'язує задачу - вертає 0 для вершини, 2 для сторони, 1 для всередині, -1 для ззовні, -2 для некоретного чотирикутника
    operator std::string() const;
    Point find_line(const Point&)const;//для заданої точки знаходить пряму, що не проходить через жодну з вершин чотирикутника (повертає точку на цій прямій)
    std::string error_details()const;//виводить повідомлення про помилку (з уточненням)
    std::string interpret_results(const Point&)const;//видає повідомлення про кінцевий результат розв'язку задачі
private:
    std::string details;
    bool validity;
    static const int N=4;
    const char name[N]={'A','B','C','D'};
    Point vertex[N+1];
};

#endif // QUADR_H_INCLUDED
