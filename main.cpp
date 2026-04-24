#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;
    
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    int getDaysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return month_days[month];
    }
    
    bool isValidDate(int year, int month, int day) const {
        if (year < 1900 || year > 2030) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(year, month)) return false;
        return true;
    }
    
public:
    Date() : _year(1900), _month(1), _day(1) {}
    
    Date(int year, int month, int day) {
        if (isValidDate(year, month, day)) {
            _year = year;
            _month = month;
            _day = day;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }
    
    Date& operator++() {
        _day++;
        if (_day > getDaysInMonth(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }
    
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }
    
    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getDaysInMonth(_year, _month);
        }
        return *this;
    }
    
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }
    
    Date operator+(int days) const {
        Date result = *this;
        while (days > 0) {
            int daysInMonth = result.getDaysInMonth(result._year, result._month);
            int daysLeftInMonth = daysInMonth - result._day;
            
            if (days <= daysLeftInMonth) {
                result._day += days;
                days = 0;
            } else {
                days -= (daysLeftInMonth + 1);
                result._day = 1;
                result._month++;
                if (result._month > 12) {
                    result._month = 1;
                    result._year++;
                }
            }
        }
        return result;
    }
    
    Date operator-(int days) const {
        Date result = *this;
        while (days > 0) {
            if (days < result._day) {
                result._day -= days;
                days = 0;
            } else {
                days -= result._day;
                result._month--;
                if (result._month < 1) {
                    result._month = 12;
                    result._year--;
                }
                result._day = result.getDaysInMonth(result._year, result._month);
            }
        }
        return result;
    }
    
    int operator-(const Date& other) const {
        Date d1 = *this;
        Date d2 = other;
        
        int days = 0;
        if (d1 < d2) {
            swap(d1, d2);
        }
        
        while (!(d1._year == d2._year && d1._month == d2._month && d1._day == d2._day)) {
            ++d2;
            days++;
        }
        
        return days;
    }
    
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }
    
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl;
        for (int i=0;i<5;++i) cout << d0++ << endl;
        for (int i=0;i<5;++i) cout << d0-- << endl;
        for (int i=0;i<2;++i) cout << --d0 << endl;
        cout << d0 << endl;
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        cout << d0 - 1000 << endl;
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}
