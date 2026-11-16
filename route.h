#pragma once 
#include <string>
#include <iostream>

class Route {
private:
    std::string point_a;
    std::string point_b;
    int number;
public:
    Route();
    Route(const std::string& p_a, const std::string& p_b, int n);
    Route(const Route& other);

    ~Route();

    std::string getPoint_a() const {return point_a;}
    void setPoint_a(const std::string& p_a) {point_a=p_a;}

    std::string getPoint_b() const {return point_b;}
    void setPoint_b(const std::string& p_b) {point_b=p_b;}

    int getNumber() const {return number;}
    void setNumber(const int n) {number=n;}

    friend std::istream& operator>>(std::istream& in, Route& route);
    friend std::ostream& operator<<(std::ostream& on, const Route& route);
};

