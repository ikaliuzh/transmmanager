#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

class Date{
public:
    Date(int h, int m, int s);

    Date(int d, int h, int m, int s);

    explicit Date(int seconds);

    Date();

    [[nodiscard]] int get() const;

    [[nodiscard]] std::string str() const;

    void set_d(int d);

    std::string print() const;

private:
    int _d, _h, _m, _s;
};

std::istream& operator>>(std::istream& stream, Date& date);

std::ostream& operator<<(std::ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);

Date operator-(const Date& lhs, const Date& rhs);

Date operator+(const Date& lhs, const Date& rhs);

