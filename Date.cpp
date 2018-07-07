#include<iostream>
using namespace std;

class Date{
    friend ostream& operator<<(ostream& os, const Date&d);
    friend ostream& operator>>(ostream& in, const Date&d);
public:
    Date(int year = 2018, int month = 7,int day = 1)
        :_year(year),
        _month(month),
        _day(day)
    {
        cout << "create function" << endl;
        if(IsInvalidDate())
        {
            _year = 2018;
            _month = 7;
            _day = 1;
        }
    }
    Date(Date& d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
        cout << "copy create function" << endl;
    }
    Date& operator=(const Date& d)
    {
        if(this != &d)
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;
    }


public:
    bool IsInvalidDate()
    {
        if((_year < 1)
           || ((_month < 1) || (_month > 12))
           || ((_day < 1) || (_day > DayInMonth())))
        {
            return true;
        }
        return false;
    }
    int DayInMonth()
    {
        int Months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(IsLeapYear())
        {
            Months[2] += 1;
        }
        return Months[_month];
    }

    bool IsLeapYear()
    {
        if(((_year % 4 == 0) && (_year % 100 != 0))
           || (_year % 400 == 0))
            return true;
        return false;
    }

    void ToCorrectDate()
    {
        while(_day <= 0){
            if(_month == 1){
                _month = 12;
                _year -= 1;
            }
            _month -= 1;
            _day += DayInMonth();
        }
        while(_day > DayInMonth())
        {
            _day -= DayInMonth();
            _month += 1;
            if(_month > 12)
            {
                _year += 1;
                _month = 1;
            }
        }
    }
    bool operator==(const Date& d)
    {
        if((_year == d._year)
           && (_month == d._month)
           && (_day == d._day))
            return true;
        return false;
    }
    bool operator>(const Date& d)
    {
        if(_year > d._year)
            return true;
        if(_year == d._year)
        {
            if(_month > d._month)
                return true;
            if(_month == d._month)
            {
                if(_day > d._day)
                    return true;
            }
        }
        return false;
    }
    bool operator>=(const Date& d)
    {
        return (*this>d)||(*this == d);
    }
    bool operator<=(const Date& d)
    {
        return !(*this>d);
    }
    bool operator<(const Date& d)
    {
        return !(*this>=d);
    }
    bool operator!=(const Date& d)
    {
        return !(*this == d);
    }
    Date operator+(int day)
    {
        Date d(*this);
        d._day += day;
        d.ToCorrectDate();
        return d;
    }
    Date operator-(int day)
    {
        Date d(*this);
        d._day -= day;
        d.ToCorrectDate();
        return d;
    }
    int operator-(Date& d)
    {
        int days = 0;
        Date d1(d);
        Date d2(*this);
        if(d1 > d2)
        {
            d1 = (*this);
            d2 = d;
        }
        while(d1 != d2)
        {
            days++;
            d1+=1;
        }
        return days;
    }
    Date& operator+=(int day)
    {
        _day += day;

        this->ToCorrectDate();
        return *this;
    }

    Date& operator-=(int day)
    {
        _day -= day;

        this->ToCorrectDate();
        return *this;
    }
private:
    int _year;
    int _month;
    int _day;
};

ostream& operator<<(ostream& os, const Date&d)
{
    os << d._year << " " << d._month << " " << d._day;
    return os;
}

istream& operator>>(istream& in, const Date&d)
{
    return in;
}
int main()
{
    /*Date d(2018, 7, 7);
    Date d1(1995, 6, 23);
    Date d2;
    d2 = d - 100;
    cout<<d2<<endl;*/
    Date d1(1995, 6, 23);
    Date d2(2018, 7, 7);
    cout<< d2-d1<<endl;
    return 0;
}

