#include "date.h"


Date::Date(int h, int m, int s):
        _h(h), _m(m), _s(s), _d(0){
    if (!(_h >= 0 && _h <= 23))
        throw std::range_error("Date::Incorrect time format::Hours");
    if (!(_m >= 0 && _m <= 59))
        throw std::range_error("Date::Incorrect time format::Minutes");
    if (!(_s >= 0 && _s <= 59))
        throw std::range_error("Date::Incorrect time format::Seconds");
}

Date::Date(int d, int h, int m, int s):
        _h(h), _m(m), _s(s), _d(d){
    if (!(_h >= 0 && _h <= 23))
        throw std::range_error("Date::Incorrect time format::Hours");
    if (!(_m >= 0 && _m <= 59))
        throw std::range_error("Date::Incorrect time format::Minutes");
    if (!(_s >= 0 && _s <= 59))
        throw std::range_error("Date::Incorrect time format::Seconds");
}

Date::Date(int seconds){
    if (seconds < 0)
        throw std::range_error("Date::Incorrect time::Negative value");
    _d = seconds /(24 * 3600);
    seconds %= 24 * 3600;
    _h = seconds / 3600;
    _m = (seconds % 3600) / 60;
    _s = seconds % 60;
    if (!(_h >= 0 && _h <= 23))
        throw std::range_error("Date::Incorrect time format::Hours");
    if (!(_m >= 0 && _m <= 59))
        throw std::range_error("Date::Incorrect time format::Minutes");
    if (!(_s >= 0 && _s <= 59))
        throw std::range_error("Date::Incorrect time format::Seconds");
}

Date::Date(): _d(0), _h(0), _m(0), _s(0) {}

[[nodiscard]] int Date::get() const{
    return _d * 24 * 3600 + _h * 3600 + _m * 60 + _s;
}

[[nodiscard]] std::string Date::str() const{
    std::stringstream ss;
    ss << _d << "d " <<
       std::setfill('0') << std::setw(2) << _h << ':'
       << std::setfill('0') << std::setw(2) << _m << ':'
       << std::setfill('0') << std::setw(2) << _s;
    return ss.str();
}

void Date::set_d(int d){
    _d = d;
}

std::string Date::print() const{
    std::stringstream ss;
    ss << _h + _d * 24 << "h " << _m << "min ";
    return ss.str();
}

std::istream& operator>>(std::istream& stream, Date& date){
    int h, m, s;
    stream >> h;
    if (stream.peek() != ':') throw std::logic_error("Failed to read date");
    stream.ignore();
    stream >> m;
    if (stream.peek() != ':') throw std::logic_error("Failed to read date");
    stream.ignore();
    stream >> s;
    date = Date{h, m, s};
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Date& date){
    stream << date.str();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs){
    return lhs.get() < rhs.get();
}

bool operator<=(const Date& lhs, const Date& rhs){
    return lhs.get() <= rhs.get();
}

bool operator==(const Date& lhs, const Date& rhs){
    return lhs.get() == rhs.get();
}

bool operator>(const Date& lhs, const Date& rhs){
    return lhs.get() > rhs.get();
}

bool operator>=(const Date& lhs, const Date& rhs){
    return lhs.get() >= rhs.get();
}

bool operator!=(const Date& lhs, const Date& rhs){
    return lhs.get() != rhs.get();
}

Date operator-(const Date& lhs, const Date& rhs){
    return Date(lhs.get() - rhs.get());
}

Date operator+(const Date& lhs, const Date& rhs){
    return Date(lhs.get() + rhs.get());
}

