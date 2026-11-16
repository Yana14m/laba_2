#include <iostream>
#include "route.h"
using namespace std;

Route::Route():point_a("Нет начального пункта"), point_b("Нет конечного пункта"), number(0) {
    cout<<"Вызван конструктор Route без параметров\n";
} 

Route::Route(const string& p_a, const string& p_b, int n): point_a(p_a), point_b(p_b), number(n) {
    cout<<"Вызван конструктор Route с параметрами\n";
}

Route::Route(const Route& other): point_a(other.point_a), point_b(other.point_b), number(other.number) {
    cout<<"Вызван конструктор копирования Route\n";
} 

Route::~Route() {
    cout<<"Вызван деструктор Route\n";
}

std::istream& operator>>(std::istream& in, Route& r) {
    std::getline(in>>std::ws, r.point_a);
    std::getline(in>>std::ws, r.point_b);
    in>>r.number;
    return in;
}

std::ostream& operator<<(std::ostream& on, const Route& r) {
    on<<"Начальный пункт: "<<r.point_a<<"\nКонечный пункт: "<<r.point_b<<"\nНомер маршрута: "<<r.number<<"\n";
    return on;
}