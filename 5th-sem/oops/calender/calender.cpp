#include <bits/stdc++.h>
using namespace std;

// wrire a program to implement a calender using operator overloading
// (1) Give input a date and print the day (like sunday ...)
// (2) Check no of days in current month (Take input from the user like year and month)
// (3) Check wether current year is a leap year or not

class calender
{
    int day;
    int month;
    int year;

public:
    calender(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
    calender(calender &c)
    {
        day = c.day;
        month = c.month;
        year = c.year;
    }
    calender operator==(calender c)
    {
        if (day == c.day && month == c.month && year == c.year)
        {
            cout << "equal" << endl;
        }
        else
        {
            cout << "not equal" << endl;
        }
        return c;
    }
    // return the days between two dates
    int operator-(calender c)
    {
        int days = 0;
        int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (year % 4 == 0)
        {
            monthDays[1] = 29;
        }
        if (year == c.year)
        {
            if (month == c.month)
            {
                days = day - c.day;
            }
            else
            {
                for (int i = month; i < c.month; i++)
                {
                    days += monthDays[i];
                }
                days = days - day + c.day;
            }
        }
        else
        {
            for (int i = year; i < c.year; i++)
            {
                if (i % 4 == 0)
                {
                    days += 366;
                }
                else
                {
                    days += 365;
                }
            }
            for (int i = month; i < 12; i++)
            {
                days += monthDays[i];
            }
            days = days - day;
            for (int i = 0; i < c.month; i++)
            {
                days += monthDays[i];
            }
            days = days + c.day;
        }
        return days;
    }
    void printDay()
    {
        int d = day;
        int m = month;
        int y = year;
        int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        int day = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
        switch (day)
        {
        case 0:
            cout << "Sunday" << endl;
            break;
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        }
    }

    bool checkLeapYear()
    {
        if (year % 4 == 0)
        {
            if (year % 100 == 0)
            {
                if (year % 400 == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    int checkDays()
    {
        int days;
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            days = 31;
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            days = 30;
        }
        else
        {
            if (checkLeapYear())
            {
                days = 29;
            }
            else
            {
                days = 28;
            }
        }
        return days;
    }

    void display()
    {
        cout << day << "/" << month << "/" << year << endl;
    }
};

int main()
{
    cout << "Enter the date 1 in dd/mm/yyyy format" << endl;
    int d, m, y;
    cin >> d >> m >> y;
    cout << "Enter the date 2 in dd/mm/yyyy format" << endl;
    int d1, m1, y1;
    cin >> d1 >> m1 >> y1;
    calender c1(d, m, y), c2(d1, m1, y1), c3(3, 4, 2020);
    c1.display();
    c2.display();
    c3.display();
    c3 = c1 == c2;
    c1.printDay();
    cout << c1.checkDays() << endl;
    if (c1.checkLeapYear())
    {
        cout << "Leap Year" << endl;
    }
    else
    {
        cout << "Not a Leap Year" << endl;
    }
    int numberofdaysbetween = c1 - c2;
    cout << "The number of days between the two dates is " << numberofdaysbetween << endl;
    return 0;
}